// Space Tanks projectiles class
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

#include "projectiles.h"
#include "spacetanks.h"
#include "shapes.h"
#include "collisions.h"
#include "particles.h"
#include "enemytanks.h"

static constexpr int kMaxProjectiles = 5;
static constexpr StandardFixedTranslationScalar kTranslationSpeed = 8.f * (float) kPerSecondMultiplier;
static constexpr int kLifeTicks = (int) (kFramesPerSecond * 1.5f);

static int s_numActiveProjectiles = 0;

// An individual projectile
class Projectile
{
public:
    bool IsActive() const { return m_active; }

    void Update()
    {
        if(--m_numTicksRemaining == 0)
        {
            DeActivate();
            return;
        }
        m_modelToWorld.translate(m_stepWorldSpace);
        CollisionTester collisionTester(m_modelToWorld.t, m_stepWorldSpace, 0.01f, m_collisionMask);
        CollisionInfo collisionInfo;
        if(Collisions::Test(collisionTester, false/*justDoCircles*/, &collisionInfo))
        {
            DeActivate();
            const uint collisionObjectMask = collisionInfo.object->GetMask();
            if((collisionObjectMask & (kCollisionMaskProjectileObstacle | kCollisionMaskEnemy)) != 0)
            {
                collisionInfo.pos.y = m_modelToWorld.t.y;
                Particles::Spawn(collisionInfo.pos, collisionInfo.normal, m_stepWorldSpace, 64);
            }
            if(collisionObjectMask & kCollisionMaskEnemy)
            {
                // This is a poor separation of concerns.
                // But it's a simple enough game - so meh.
                EnemyTanks::Destroy(*collisionInfo.object);
            }
            return;
        }
    }

    void Draw(DisplayList& displayList, const Camera& camera) const
    {
        GetFixedShape(FixedShape::Projectile).Draw(displayList, m_modelToWorld, camera, kIntensityAdjustment * 1.5f);
    }

    void Activate(const FixedTransform3D& parent, uint collisionMask)
    {
        m_active = true;
        ++s_numActiveProjectiles;
        m_numTicksRemaining = kLifeTicks;
        m_collisionMask = collisionMask;
        m_modelToWorld = parent;
        m_modelToWorld.rotateVector(m_stepWorldSpace, StandardFixedTranslationVector(kTranslationSpeed, 0, 0));
    }

    void DeActivate()
    {
        m_active = false;
        --s_numActiveProjectiles;
    }

private:
    bool      m_active;
    int       m_numTicksRemaining;
    uint      m_collisionMask;
    FixedTransform3D m_modelToWorld;
    StandardFixedTranslationVector m_stepWorldSpace;
};

static Projectile s_projectiles[kMaxProjectiles] = {};


void Projectiles::Reset()
{
    for(Projectile& projectile : s_projectiles)
    {
        if(projectile.IsActive()) projectile.DeActivate();
    }
}

void Projectiles::Update()
{
    for(Projectile& projectile : s_projectiles)
    {
        if(projectile.IsActive()) projectile.Update();
    }
}

void Projectiles::Draw(DisplayList& displayList, const Camera& camera)
{
    for(const Projectile& projectile : s_projectiles)
    {
        if(projectile.IsActive()) projectile.Draw(displayList, camera);
    }
}

void Projectiles::Create(int idx, const FixedTransform3D& parent, uint collisionMask)
{
    Projectile& projectile = s_projectiles[idx];
    assert(!projectile.IsActive());
    if(!projectile.IsActive())
    {
        projectile.Activate(parent, collisionMask);
    }
}

bool Projectiles::IsActive(int idx)
{
    return s_projectiles[idx].IsActive();
}
