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

#pragma once
#include "picovectorscope.h"
#include "extras/camera.h"


// Static class to manage _all_ the particles
class Particles
{
public:    
    static void Reset();
    static void Update();
    static void Draw(DisplayList& displayList, const Camera& camera);

    static void Spawn(const StandardFixedTranslationVector& pos,
                      const StandardFixedOrientationVector& normal,
                      const StandardFixedTranslationVector& impactVelocity,
                      int count);
};

class ParticleBase
{
public:
    ParticleBase();

    bool IsActive() const { return m_numTicksRemaining != 0; }

    void Update();
    void Activate(const StandardFixedTranslationVector& pos, const StandardFixedTranslationVector& velocity);
    void DeActivate();

protected:
    StandardFixedTranslationVector m_pos;
    StandardFixedTranslationVector m_velocity;
    uint m_numTicksRemaining;
    uint m_startTicks;
    Intensity m_startIntrinsicBrightness;
    Intensity m_intrinsicBrightness;
    StandardFixedTranslationScalar m_recipTotalTicks;
};
