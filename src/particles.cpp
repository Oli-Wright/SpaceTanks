// Space Tanks particles management
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

#include "particles.h"
#include "extras/shapes3d.h"
#include "spacetanks.h"
#include "maths.h"

static constexpr int kMaxParticles = 128;

LogChannel s_particlesLog(false);


ParticleBase::ParticleBase()
{
    m_numTicksRemaining = 0;
    StandardFixedTranslationScalar relLife = StandardFixedTranslationScalar::randZeroToOne() * 0.75f + 0.25f;
    m_startIntrinsicBrightness = relLife * 0.3f;
    m_startTicks = (uint) (relLife * kFramesPerSecond);
    m_recipTotalTicks = StandardFixedTranslationScalar(1.f) / StandardFixedTranslationScalar(m_startTicks);
}

void ParticleBase::Update()
{
    if(--m_numTicksRemaining == 0)
    {
        DeActivate();
        return;
    }
    m_velocity.y -= 0.0001f;
    m_velocity *= 0.999f;
    m_pos += m_velocity;
    if(m_pos.y < 0)
    {
        m_pos.y = 0;
        m_velocity *= StandardFixedTranslationVector(0.75f, -0.5f, 0.75f);
    }
    m_intrinsicBrightness = m_recipTotalTicks * (int) m_numTicksRemaining * m_startIntrinsicBrightness;
}

void ParticleBase::Activate(const StandardFixedTranslationVector& pos, const StandardFixedTranslationVector& velocity)
{
    m_numTicksRemaining = m_startTicks;
    m_intrinsicBrightness = m_startIntrinsicBrightness;
    m_pos = pos;
    m_velocity = velocity;
}

void ParticleBase::DeActivate()
{
    m_numTicksRemaining = false;
}

// An individual particle
class Particle : public ParticleBase
{
public:
    void Draw(DisplayList& displayList, const Camera& camera) const
    {
        Shape3D::DrawPoint(displayList, m_pos, camera, m_intrinsicBrightness);
    }
};

static Particle s_particles[kMaxParticles];


void Particles::Reset()
{
    for(Particle& particle : s_particles)
    {
        if(particle.IsActive()) particle.DeActivate();
    }
}

void Particles::Update()
{
    for(Particle& particle : s_particles)
    {
        if(particle.IsActive()) particle.Update();
    }
}

void Particles::Draw(DisplayList& displayList, const Camera& camera)
{
    for(const Particle& particle : s_particles)
    {
        if(particle.IsActive()) particle.Draw(displayList, camera);
    }
}

static void normalise(StandardFixedOrientationVector& vec)
{
    StandardFixedOrientationScalar length = ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)).sqrt();
    StandardFixedOrientationScalar recipLength = length.recip();
    vec *= recipLength;
}

void Particles::Spawn(const StandardFixedTranslationVector& pos,
                      const StandardFixedOrientationVector& normal,
                      const StandardFixedTranslationVector& impactVelocity,
                      int count)
{
    // Create a basis matrix for spawnage
    // The y axis will align with the normal, and we don't care about the order
    // or sign of the x and z axes, as long as they're normalish and perpendicular.
    FixedTransform3D particleSpawnToWorld;
    particleSpawnToWorld.markAsManuallyManipulated();
    particleSpawnToWorld.m[1] = normal;
    particleSpawnToWorld.m[0] = cross(normal, StandardFixedOrientationVector(0, 1, 0));
    normalise(particleSpawnToWorld.m[0]);
    particleSpawnToWorld.m[2] = cross(normal, particleSpawnToWorld.m[0]);
    particleSpawnToWorld.t = pos;
    LOG_INFO(s_particlesLog, "\n%f, %f, %f\n", (float) particleSpawnToWorld.m[0].x, (float) particleSpawnToWorld.m[0].y, (float) particleSpawnToWorld.m[0].z);
    LOG_INFO(s_particlesLog, "%f, %f, %f\n", (float) particleSpawnToWorld.m[1].x, (float) particleSpawnToWorld.m[1].y, (float) particleSpawnToWorld.m[1].z);
    LOG_INFO(s_particlesLog, "%f, %f, %f\n", (float) particleSpawnToWorld.m[2].x, (float) particleSpawnToWorld.m[2].y, (float) particleSpawnToWorld.m[2].z);
    LOG_INFO(s_particlesLog, "Pos: %f, %f, %f\n", (float) pos.x, (float) pos.y, (float) pos.z);
    LOG_INFO(s_particlesLog, "Vel: %f, %f, %f\n", (float) impactVelocity.x, (float) impactVelocity.y, (float) impactVelocity.z);

    // Transform the impact velocity vector into particle spawn space
    FixedTransform3D worldToParticleSpawn;
    particleSpawnToWorld.orthonormalInvert(worldToParticleSpawn);

    StandardFixedTranslationVector spawnVelocitySpawnSpace;
    worldToParticleSpawn.rotateVector(spawnVelocitySpawnSpace, impactVelocity);
    spawnVelocitySpawnSpace.y = 0;

    for(Particle& particle : s_particles)
    {
        if(!particle.IsActive())
        {
            // Create a particle
            StandardFixedTranslationVector velocity;
            velocity.x = StandardFixedTranslationScalar::randMinusOneToOne();
            velocity.y = StandardFixedTranslationScalar::randZeroToOne() * 0.5f;
            velocity.z = StandardFixedTranslationScalar::randMinusOneToOne();
            velocity *= kPerSecondMultiplier * 3.f;
            velocity += spawnVelocitySpawnSpace * 0.25f; // Use a fraction of the impact velocity
            StandardFixedTranslationVector velocityWorldSpace;
            particleSpawnToWorld.rotateVector(velocityWorldSpace, velocity);
            LOG_INFO(s_particlesLog, "VelWS: %f, %f, %f\n", (float) velocityWorldSpace.x, (float) velocityWorldSpace.y, (float) velocityWorldSpace.z);
            particle.Activate(pos, velocityWorldSpace);
            if(--count == 0) break;
        }
    }
}

