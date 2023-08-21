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

#include "collisions.h"

static constexpr uint kMaxCollisionObjects = 48;
LogChannel s_collisionLog(false);

static CollisionObject s_collisionObjects[kMaxCollisionObjects] = {};

void CollisionObject::Configure(const FixedTransform3D& modelToWorld,
                                StandardFixedTranslationScalar halfBoxWidth,
                                uint mask,
                                SinTable::Index surfaceAngle)
{
    m_localToWorld.m[0] = CollisionTransform2D::OrientationVectorType(modelToWorld.m[0].x, modelToWorld.m[0].z);
    m_localToWorld.m[1] = CollisionTransform2D::OrientationVectorType(modelToWorld.m[2].x, modelToWorld.m[2].z);
    m_localToWorld.t = m_pos = CollisionTransform2D::TranslationVectorType(modelToWorld.t.x, modelToWorld.t.z);
    m_localToWorld.orthonormalInvert(m_worldToLocal);
    m_mask = mask;
    m_halfBoxWidth = halfBoxWidth;
    m_radius = halfBoxWidth * 1.4142136f;
    m_surfaceAngle = surfaceAngle;
}

CollisionTester::CollisionTester(const StandardFixedTranslationVector& pos,
                                 const StandardFixedTranslationVector& deltaPos,
                                 StandardFixedTranslationScalar radius,
                                 uint mask)
: m_pos(CollisionTransform2D::TranslationVectorType(pos.x, pos.z))
, m_deltaPos(CollisionTransform2D::TranslationVectorType(deltaPos.x, deltaPos.z))
, m_radius(radius)
, m_mask(mask)
{}

void Collisions::Reset()
{
    for(CollisionObject& object : s_collisionObjects)
    {
        object.m_mask = 0;
    }
}

CollisionObject& Collisions::AllocateObject()
{
    for(CollisionObject& object : s_collisionObjects)
    {
        if(object.m_mask == 0)
        {
            object.m_mask = 0x1000; //< Just make it non-zero until it gets configured
            return object;
        }
    }
    // We've run out of collision objects
    assert(false);
    return *(CollisionObject*)nullptr;
}

void Collisions::FreeObject(CollisionObject& object)
{
    object.m_mask = 0;
}

const bool Collisions::Test(const CollisionTester& test, bool justDoCircles, CollisionInfo* outCollisionInfo)
{
    StandardFixedTranslationScalar closestSeparationSquared = -1;
    const CollisionObject* closestObject = nullptr;
    for(const CollisionObject& object : s_collisionObjects)
    {
        if((object.m_mask & test.m_mask) != 0)
        {
            // Test the distance of this object pair to see if they overlap
            const StandardFixedTranslationScalar dx = Abs(object.m_pos.x - test.m_pos.x);
            const StandardFixedTranslationScalar dz = Abs(object.m_pos.y - test.m_pos.y);
            const StandardFixedTranslationScalar minManhattenSeparation = (object.m_halfBoxWidth + test.m_radius) << 1;
            // First we'll consider the Manhatten distance. Both as an early-out
            // and also to prevent us from trying to square large numbers which
            // might overflow
            StandardFixedTranslationScalar manhattenDistance = dx + dz;
            if(manhattenDistance > minManhattenSeparation)
            {
                // Can't be overlapping
                continue;
            }
            const StandardFixedTranslationScalar centreDistanceSquared = ((dx * dx) + (dz * dz));
            const StandardFixedTranslationScalar minCircleSeparation = object.m_radius + test.m_radius;
            const StandardFixedTranslationScalar separationSquaredKinda = centreDistanceSquared - (minCircleSeparation * minCircleSeparation);
            if(separationSquaredKinda > 0)
            {
                // Not overlapping
                continue;
            }
            if(justDoCircles)
            {
                if((closestObject != nullptr) && (separationSquaredKinda > closestSeparationSquared))
                {
                    // Overlapping, but not the closest
                    continue;
                }
            }
            else
            {
                // Test the box.
                // To do this, we must transform the test point into the space of
                // the collision object.
                CollisionTransform2D::TranslationVectorType testPosInObjectSpace;
                object.m_worldToLocal.transformVector(testPosInObjectSpace, test.m_pos);
                StandardFixedTranslationScalar extendedHalfBoxWidth = object.m_halfBoxWidth + test.m_radius;
                LOG_INFO(s_collisionLog, "---\nTestPos: %f, %f\n", (float) testPosInObjectSpace.x, (float) testPosInObjectSpace.y);
                if((Abs(testPosInObjectSpace.x) > extendedHalfBoxWidth) || (Abs(testPosInObjectSpace.y) > extendedHalfBoxWidth))
                {
                    continue;
                }

                if(outCollisionInfo != nullptr)
                {
                    // Now we look at the deltas and figure out which side of the box we've crossed
                    CollisionTransform2D::TranslationVectorType testDeltaPosInObjectSpace;
                    object.m_worldToLocal.rotateVector(testDeltaPosInObjectSpace, test.m_deltaPos);
                    // We want to work with -ve deltas, and +ve edges
                    bool flipX = false;
                    bool flipY = false;
                    if(testDeltaPosInObjectSpace.x > 0)
                    {
                        flipX = true;
                        testDeltaPosInObjectSpace.x = -testDeltaPosInObjectSpace.x;
                        testPosInObjectSpace.x = -testPosInObjectSpace.x;
                    }
                    if(testDeltaPosInObjectSpace.y > 0)
                    {
                        flipY = true;
                        testDeltaPosInObjectSpace.y = -testDeltaPosInObjectSpace.y;
                        testPosInObjectSpace.y = -testPosInObjectSpace.y;
                    }
                    LOG_INFO(s_collisionLog, "Flip: %d, %d\n", flipX, flipY);
                    const StandardFixedTranslationScalar shrunkHalfBoxWidth = object.m_halfBoxWidth;// - test.m_radius;
                    const CollisionTransform2D::TranslationVectorType testPreviousPosInObjectSpace = testPosInObjectSpace - testDeltaPosInObjectSpace;
                    LOG_INFO(s_collisionLog, "TestPos: %f, %f\n", (float) testPosInObjectSpace.x, (float) testPosInObjectSpace.y);
                    LOG_INFO(s_collisionLog, "PrevPos: %f, %f\n", (float) testPreviousPosInObjectSpace.x, (float) testPreviousPosInObjectSpace.y);

                    const bool crossedX = (testPosInObjectSpace.x < shrunkHalfBoxWidth) && (testPreviousPosInObjectSpace.x >= shrunkHalfBoxWidth);
                    const bool crossedY = (testPosInObjectSpace.y < shrunkHalfBoxWidth) && (testPreviousPosInObjectSpace.y >= shrunkHalfBoxWidth);
                    if(!crossedX && !crossedY)
                    {
                        continue; // Precision?
                    }
                    StandardFixedTranslationScalar xt = 0;
                    StandardFixedTranslationScalar yt = 0;
                    if(crossedX)
                    {
                        xt = (shrunkHalfBoxWidth - testPosInObjectSpace.x) / (testPreviousPosInObjectSpace.x - testPosInObjectSpace.x);
                    }
                    if(crossedY)
                    {
                        yt = (shrunkHalfBoxWidth - testPosInObjectSpace.y) / (testPreviousPosInObjectSpace.y - testPosInObjectSpace.y);
                    }
                    CollisionTransform2D::TranslationVectorType hitPosLocal;
                    CollisionTransform2D::OrientationVectorType hitNormalLocal;
                    SinTableValue surfaceSin = 0, surfaceCos = 1;
                    if(object.m_surfaceAngle != 0)
                    {
                        SinTable::SinCos(object.m_surfaceAngle, surfaceSin, surfaceCos);
                    }
                    if(xt > yt)
                    {
                        // Hit the x
                        hitPosLocal = testPreviousPosInObjectSpace + (testDeltaPosInObjectSpace * xt);
                        hitNormalLocal = CollisionTransform2D::OrientationVectorType(surfaceCos, 0);
                    }
                    else
                    {
                        // Hit the y
                        hitPosLocal = testPreviousPosInObjectSpace + (testDeltaPosInObjectSpace * yt);
                        hitNormalLocal = CollisionTransform2D::OrientationVectorType(0, surfaceCos);
                    }
                    if(flipX)
                    {
                        hitPosLocal.x = -hitPosLocal.x;
                        hitNormalLocal.x = -hitNormalLocal.x;
                    }
                    if(flipY)
                    {
                        hitPosLocal.y = -hitPosLocal.y;
                        hitNormalLocal.y = -hitNormalLocal.y;
                    }
                    CollisionTransform2D::TranslationVectorType pos;
                    CollisionTransform2D::OrientationVectorType normal;                    
                    object.m_localToWorld.transformVector(pos, hitPosLocal);
                    object.m_localToWorld.rotateVector(normal, hitNormalLocal);
                    outCollisionInfo->pos = StandardFixedTranslationVector(pos.x, 0, pos.y);
                    outCollisionInfo->normal = StandardFixedOrientationVector(normal.x, surfaceSin, normal.y);
                    outCollisionInfo->object = &object;
                }
            }

            // Overlappingest so far
            closestObject = &object;
            closestSeparationSquared = separationSquaredKinda;
        }
    }
    return closestObject;
}
