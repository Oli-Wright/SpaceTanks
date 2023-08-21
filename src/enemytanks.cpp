// Space Tanks enemy tank class
//
// Copyright (C) 2023 Oli Wright
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// A copy of the GNU General Public License can be found in the file
// LICENSE.txt in the root of this project.
// If not, see <https://www.gnu.org/licenses/>.
//
// oli.wright.github@gmail.com

#include "enemytanks.h"
#include "spacetanks.h"
#include "player.h"
#include "projectiles.h"
#include "particles.h"
#include "collisions.h"
#include "shapes.h"

static constexpr Angle kRadarDishRotationSpeed = 3.f * (float) kPerSecondMultiplier;
static constexpr StandardFixedTranslationScalar kRadarDishOffsetZ = -0.5f;
static constexpr Angle kRotationSpeed = 0.3f * (float) kPerSecondMultiplier;
static constexpr Angle kAimAngleTolerance = kPi * 0.001f;
static constexpr StandardFixedTranslationScalar kTranslationSpeed = 2.f * (float) kPerSecondMultiplier;
//static constexpr int kCoolDownTicks = 2 * (int_fast16_t) kFramesPerSecond;
static constexpr int kNumDebrisChunks = 5;

enum class Behaviour
{
    TurnToPlayer,
    Move,
    Dead,

    Count
};

static constexpr int kNumTicksInBehaviourPhase[] = 
{
    (int) (kFramesPerSecond * 6.f ), // TurnToPlayer
    (int) (kFramesPerSecond * 1.5f), // Move
    (int) (kFramesPerSecond * 4.f),  // Dead
};
static_assert(count_of(kNumTicksInBehaviourPhase) == (size_t) Behaviour::Count, "");

static int s_numActiveTanks = 0;

class DebrisChunk : public ParticleBase
{
public:
    DebrisChunk() : ParticleBase()
    , m_shape(FixedShape::Chunk0)
    {}

    void Activate(const StandardFixedTranslationVector& pos, const StandardFixedTranslationVector& velocity)
    {
        ParticleBase::Activate(pos, velocity);

        StandardFixedOrientationVector rotationAngles;
        static const float kMaxRadsPerSecond = 0.2f;
        rotationAngles.x = StandardFixedTranslationScalar::randMinusOneToOne() * kMaxRadsPerSecond * kPerSecondMultiplier;
        rotationAngles.y = StandardFixedTranslationScalar::randMinusOneToOne() * kMaxRadsPerSecond * kPerSecondMultiplier;
        rotationAngles.z = StandardFixedTranslationScalar::randMinusOneToOne() * kMaxRadsPerSecond * kPerSecondMultiplier;
        m_rotation.setRotationXYZ(rotationAngles.x, rotationAngles.y, rotationAngles.z);
        m_rotation.setTranslation(StandardFixedTranslationVector(0, 0, 0));

        m_modelToWorld.setAsIdentity();
        m_modelToWorld.markAsManuallyManipulated();
        m_modelToWorld.setTranslation(pos);
    }

    void Update()
    {
        ParticleBase::Update();
        if(!IsActive())
        {
            return;
        }
        m_modelToWorld *= m_rotation;
        m_modelToWorld.t = m_pos;
    }

    void Draw(DisplayList& displayList, const Camera& camera) const
    {
        GetFixedShape(m_shape).Draw(displayList, m_modelToWorld, camera, m_intrinsicBrightness * 3.f);
    }

    void SetShape(FixedShape shape) { m_shape = shape; }

private:
    FixedTransform3D m_modelToWorld;
    FixedTransform3D m_rotation;
    FixedShape m_shape;
};

static DebrisChunk s_debrisChunks[kNumDebrisChunks];

// An individual enemy tank
class EnemyTank
{
public:
    EnemyTank()
    : m_active(false)
    {}

    bool IsActive() const { return m_active; }

    void Respawn()
    {
        // Find a good spawn location
        while(true)
        {
            constexpr StandardFixedTranslationScalar kRange = 16;
            m_modelToWorld.t.x = StandardFixedTranslationScalar::randMinusOneToOne() * kRange;
            m_modelToWorld.t.y = 0.625f;
            m_modelToWorld.t.z = StandardFixedTranslationScalar::randMinusOneToOne() * kRange;
            break;
        }
        m_yaw = StandardFixedOrientationScalar::randZeroToOne() * (kPi * 2.f);
        m_radarDishYaw = 0;

    }

    void Update()
    {
        m_radarDishYaw += kRadarDishRotationSpeed;
        if(m_radarDishYaw > (kPi * 2))
        {
            m_radarDishYaw -= (kPi * 2);
        }
        if(--m_numTicksLeftInBehaviour == 0)
        {
            switch(m_behaviour)
            {
                case Behaviour::TurnToPlayer:
                    m_behaviour = Behaviour::Move;
                    break;
                case Behaviour::Move:
                    m_behaviour = Behaviour::TurnToPlayer;
                    break;
                case Behaviour::Dead:
                    Respawn();
                    m_behaviour = Behaviour::TurnToPlayer;
                default:
                    break;
            }
            m_numTicksLeftInBehaviour = kNumTicksInBehaviourPhase[(int) m_behaviour];
        }

        switch(m_behaviour)
        {
            case Behaviour::TurnToPlayer:
            {
                const StandardFixedTranslationVector& playerPos = Player::GetPosition();
                Angle targetYaw = StandardFixedTranslationScalar::ApproxATan2(m_modelToWorld.t.x - playerPos.x, m_modelToWorld.t.z - playerPos.z) + (kPi * 0.5f);
                Angle yawDiff = targetYaw - m_yaw;
                if(yawDiff > kPi) yawDiff -= k2Pi;
                else if(yawDiff < -kPi) yawDiff += k2Pi;
                if(yawDiff > kAimAngleTolerance)
                {
                    m_yaw += kRotationSpeed;
                    if(m_yaw > k2Pi) m_yaw -= k2Pi;
                }
                else if(yawDiff < -kAimAngleTolerance)
                {
                    m_yaw -= kRotationSpeed;
                    if(m_yaw < 0) m_yaw += k2Pi;
                }
                m_modelToWorld.setRotationXYZ(0, m_yaw, 0);
                if(!Projectiles::IsActive(m_projectileIdx) && (Abs(yawDiff) < kAimAngleTolerance))
                {
                    Projectiles::Create(m_projectileIdx, m_modelToWorld, kCollisionMaskProjectileObstacle | kCollisionMaskPlayer);
                }
                break;
            }
            case Behaviour::Move:
            {
                StandardFixedTranslationVector stepWorldSpace;
                m_modelToWorld.rotateVector(stepWorldSpace, StandardFixedTranslationVector(kTranslationSpeed, 0, 0));
                m_modelToWorld.translate(stepWorldSpace);
                break;
            }
            case Behaviour::Dead:
            {
                break;
            }
            default:
                break;
        }
        m_collisionObject->Configure(m_modelToWorld, 0.3f, kCollisionMaskEnemy, 0.3f);
    }

    void Draw(DisplayList& displayList, const Camera& camera) const
    {
        switch(m_behaviour)
        {
            case Behaviour::Dead:
                break;

            default:
            {
                // Tank
                GetFixedShape(FixedShape::Tank1).Draw(displayList, m_modelToWorld, camera, kIntensityAdjustment);
                // Radar dish
                FixedTransform3D modelToWorld;
                modelToWorld.setTranslation(m_modelToWorld * StandardFixedTranslationVector(kRadarDishOffsetZ, 0, 0));
                modelToWorld.setRotationXYZ(0, m_radarDishYaw, 0);
                GetFixedShape(FixedShape::Radar).Draw(displayList, modelToWorld, camera, kIntensityAdjustment);
                break;
            }
        }
    }

    void Destroy()
    {
        m_behaviour = Behaviour::Dead;
        m_numTicksLeftInBehaviour = kNumTicksInBehaviourPhase[(int) m_behaviour];
        for(DebrisChunk& debrisChunk : s_debrisChunks)
        {
            StandardFixedTranslationVector velocity;
            velocity.x = StandardFixedTranslationScalar::randMinusOneToOne();
            velocity.y = StandardFixedTranslationScalar::randZeroToOne();
            velocity.z = StandardFixedTranslationScalar::randMinusOneToOne();
            velocity *= kPerSecondMultiplier * 5.f;
            debrisChunk.Activate(m_modelToWorld.t, velocity);
        }
    }

    void Activate()
    {
        m_active = true;
        ++s_numActiveTanks;

        Respawn();
        m_behaviour = Behaviour::TurnToPlayer;
        m_numTicksLeftInBehaviour = kNumTicksInBehaviourPhase[(int) m_behaviour];

        m_collisionObject = &Collisions::AllocateObject();
    }

    void DeActivate()
    {
        m_active = false;
        --s_numActiveTanks;
        Collisions::FreeObject(*m_collisionObject);
        m_collisionObject = nullptr;
    }

    void SetProjectileIdx(int idx) { m_projectileIdx = idx; }

    bool OwnsCollisionObject(const CollisionObject& collisionObject) const
    {
        return (m_collisionObject == &collisionObject);
    }

    const FixedTransform3D& GetModelToWorld() const { return m_modelToWorld; }

private:
    bool      m_active;
    Angle     m_yaw;
    Angle     m_radarDishYaw;
    Behaviour m_behaviour;
    int       m_numTicksLeftInBehaviour;
    int       m_projectileIdx;
    FixedTransform3D m_modelToWorld;
    CollisionObject* m_collisionObject;
};

static EnemyTank s_enemyTanks[kMaxEnemyTanks];

void EnemyTanks::Reset()
{
    for(int i = 0; i < kMaxEnemyTanks; ++i)
    {
        EnemyTank& tank = s_enemyTanks[i];
        tank.SetProjectileIdx(i + 1);
        if(tank.IsActive()) tank.DeActivate();
    }
    s_enemyTanks[0].Activate();
    for(int i = 0; i < kNumDebrisChunks; ++i)
    {
        s_debrisChunks[i].SetShape((FixedShape)((int) FixedShape::Chunk0 + i));
    }
}

void EnemyTanks::Update()
{
    for(EnemyTank& tank : s_enemyTanks)
    {
        if(tank.IsActive()) tank.Update();
    }
    for(DebrisChunk& debrisChunk : s_debrisChunks)
    {
        if(debrisChunk.IsActive()) debrisChunk.Update();
    }
}

void EnemyTanks::Draw(DisplayList& displayList, const Camera& camera)
{
    for(const EnemyTank& tank : s_enemyTanks)
    {
        if(tank.IsActive()) tank.Draw(displayList, camera);
    }
    for(const DebrisChunk& debrisChunk : s_debrisChunks)
    {
        if(debrisChunk.IsActive()) debrisChunk.Draw(displayList, camera);
    }

}

void EnemyTanks::Destroy(const class CollisionObject& collisionObject)
{
    for(EnemyTank& tank : s_enemyTanks)
    {
        if(tank.IsActive() && tank.OwnsCollisionObject(collisionObject)) tank.Destroy();
    }
}

const FixedTransform3D* EnemyTanks::GetTransform(int idx)
{
    const EnemyTank& tank = s_enemyTanks[idx];
    return tank.IsActive() ? &tank.GetModelToWorld() : nullptr;
}
