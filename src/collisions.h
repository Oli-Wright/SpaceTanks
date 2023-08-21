// Space Tanks collision management
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
#include "transform3d.h"

static constexpr uint kCollisionMaskProjectileObstacle = (1u << 0);
static constexpr uint kCollisionMaskTankObstacle       = (1u << 1);
static constexpr uint kCollisionMaskPlayer             = (1u << 2);
static constexpr uint kCollisionMaskEnemy              = (1u << 3);

// Collisions take place on a 2D plane
// So we define a 2D transform using the same precision types as our 3D transforms
typedef Transform2D<StandardFixedOrientationScalar,StandardFixedTranslationScalar> CollisionTransform2D;

class CollisionObject
{
public:
    void Configure(const FixedTransform3D& modelToWorld,
                   StandardFixedTranslationScalar halfBoxWidth,
                   uint mask,
                   SinTable::Index surfaceAngle = 0);

    uint GetMask() const { return m_mask; }

private:
    CollisionTransform2D                        m_localToWorld;
    CollisionTransform2D                        m_worldToLocal;
    CollisionTransform2D::TranslationVectorType m_pos;
    StandardFixedTranslationScalar              m_halfBoxWidth;
    StandardFixedTranslationScalar              m_radius;
    uint                                        m_mask;
    SinTable::Index                             m_surfaceAngle;

    friend class Collisions;
};

class CollisionTester
{
public:
    CollisionTester(const StandardFixedTranslationVector& pos,
                    const StandardFixedTranslationVector& deltaPos,
                    StandardFixedTranslationScalar radius,
                    uint mask);
private:
    CollisionTransform2D::TranslationVectorType m_pos;
    CollisionTransform2D::TranslationVectorType m_deltaPos;
    StandardFixedTranslationScalar              m_radius;
    uint                                        m_mask;

    friend class Collisions;
};

struct CollisionInfo
{
    StandardFixedTranslationVector pos;
    StandardFixedOrientationVector normal;
    const CollisionObject*         object;
};

// Static class to manage collision detection
class Collisions
{
public:    
    static void Reset();
    static CollisionObject& AllocateObject();
    static void FreeObject(CollisionObject& object);

    // Test for a collision.
    // Only collision objects with at least one common mask bit with the test
    // object will be tested.
    // Returns true if there was a collision, false otherwise.
    // If outCollisionInfo is not nullptr, it will be populated with information
    // about the collision.
    static const bool Test(const CollisionTester& test, bool justDoCircles, CollisionInfo* outCollisionInfo = nullptr);
};