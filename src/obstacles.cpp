// Space Tanks obstacles
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

#include "obstacles.h"
#include "shapes.h"
#include "collisions.h"
#include "spacetanks.h"

struct ObstacleTypeDef
{
    FixedTransform3D m_modelToWorld;
    FixedShape       m_shape;
    StandardFixedTranslationScalar m_tankCollisionRadius;
    StandardFixedTranslationScalar m_projectileCollisionRadius;
    SinTable::Index  m_surfaceAngle;

    // constexpr constructor, so the array is built at compile-time
    constexpr ObstacleTypeDef(  FixedShape shape,
                                StandardFixedOrientationScalar xzScale,
                                StandardFixedOrientationScalar yScale,
                                StandardFixedTranslationScalar tankCollisionRadius,
                                StandardFixedTranslationScalar projectileCollisionRadius,
                                SinTable::Index                surfaceAngle )
    : m_modelToWorld(StandardFixedTranslationVector(0, yScale * 0.625f, 0), StandardFixedOrientationVector(xzScale, yScale, xzScale))
    , m_shape(shape)
    , m_tankCollisionRadius(tankCollisionRadius)
    , m_projectileCollisionRadius(projectileCollisionRadius)
    , m_surfaceAngle(surfaceAngle)
    {}
};
enum class ObstacleType
{
    WidePyramid,
    NarrowPyramid,
    TallBox,
    ShortBox,

    Count
};
constexpr ObstacleTypeDef kObstacleTypeDefs[] = 
{
    ObstacleTypeDef(FixedShape::Pyr, 1.5f, 1.f,  0.75f, 0.375f, 0.6435f), // WidePyramid
    ObstacleTypeDef(FixedShape::Pyr, 1.f,  1.f,  0.5f,  0.25f,  0.4636f), // NarrowPyramid
    ObstacleTypeDef(FixedShape::Box, 1.f,  1.f,  0.5f,  0.5f,   0),       // TallBox
    ObstacleTypeDef(FixedShape::Box, 1.5f, 0.5f, 0.75f, 0,      0),       // ShortBox
};
static constexpr uint kNumObstacleTypes = (uint) count_of(kObstacleTypeDefs);
static_assert(kNumObstacleTypes == (uint)ObstacleType::Count, "");

typedef FixedPoint<5, 10, int16_t, int32_t, false> ObstacleOriginalCoord;
struct ObstacleInstance
{
    StandardFixedTranslationVector m_position;
    ObstacleType                   m_type;

    // constexpr constructor, so the array is built at compile-time
    constexpr ObstacleInstance(uint16_t x, uint16_t z, ObstacleType obstacleType)
    : m_position(
        (StandardFixedTranslationScalar) ObstacleOriginalCoord((ObstacleOriginalCoord::StorageType)x),
        kObstacleTypeDefs[(uint)obstacleType].m_modelToWorld.t.y,
        (StandardFixedTranslationScalar) ObstacleOriginalCoord((ObstacleOriginalCoord::StorageType)z))
    , m_type(obstacleType)
    {}
};

constexpr ObstacleInstance kObstacles[] = 
{
    ObstacleInstance(0x2000, 0x2000, ObstacleType::WidePyramid),
    ObstacleInstance(0x4000, 0x0000, ObstacleType::ShortBox),
    ObstacleInstance(0x8000, 0x0000, ObstacleType::WidePyramid),
    ObstacleInstance(0x8000, 0x4000, ObstacleType::ShortBox),
    ObstacleInstance(0x8000, 0x8000, ObstacleType::WidePyramid),
    ObstacleInstance(0x4000, 0x8000, ObstacleType::NarrowPyramid),
    ObstacleInstance(0x0000, 0x8000, ObstacleType::TallBox),
    ObstacleInstance(0x0000, 0x4000, ObstacleType::NarrowPyramid),
    ObstacleInstance(0x5000, 0x3000, ObstacleType::TallBox),
    ObstacleInstance(0x1800, 0xc000, ObstacleType::ShortBox),
    ObstacleInstance(0x4400, 0xf700, ObstacleType::WidePyramid),
    ObstacleInstance(0x4000, 0xc800, ObstacleType::NarrowPyramid),
    ObstacleInstance(0x8c00, 0xd800, ObstacleType::TallBox),
    ObstacleInstance(0x0c00, 0x9400, ObstacleType::ShortBox),
    ObstacleInstance(0xe800, 0x9800, ObstacleType::WidePyramid),
    ObstacleInstance(0xe400, 0xe800, ObstacleType::NarrowPyramid),
    ObstacleInstance(0x9c00, 0x7000, ObstacleType::TallBox),
    ObstacleInstance(0xcc00, 0x7800, ObstacleType::ShortBox),
    ObstacleInstance(0xb400, 0x4000, ObstacleType::WidePyramid),
    ObstacleInstance(0xbc00, 0x2400, ObstacleType::NarrowPyramid),
    ObstacleInstance(0xf400, 0x2c00, ObstacleType::TallBox),
};
static constexpr uint kNumObstacles = (uint) count_of(kObstacles);

static Intensity calcIntensity(const Camera& camera, const StandardFixedTranslationVector& pos)
{
    constexpr StandardFixedTranslationScalar kMaxDist = 32.f; // Will fade to 0 at this distance
    constexpr StandardFixedTranslationScalar kMaxDistSquared = kMaxDist * kMaxDist;
    constexpr StandardFixedTranslationScalar kMaxManhattenDistance = kMaxDist * 2;
    StandardFixedTranslationVector relPosition = pos - camera.GetPosition();
    // First calculate the Manhatten distance to early out for large distances and
    // avoid calculating square distances that we can't process
    StandardFixedTranslationScalar manhatten = Abs(relPosition.x) + Abs(relPosition.z);
    if(manhatten > kMaxManhattenDistance)
    {
        return 0;
    }
    // Now we should be safe to compute the actual squared distance
    StandardFixedTranslationScalar distanceSquared = (relPosition.x * relPosition.x) + (relPosition.z * relPosition.z);
    StandardFixedTranslationScalar normDist = distanceSquared / kMaxDistSquared;
    if(normDist >= 1)
    {
        return 0;
    }
    return (Intensity(1) - normDist) * kIntensityAdjustment;
}

void Obstacles::Init()
{
    FixedTransform3D modelToWorld;
    modelToWorld.setAsIdentity();
    for(const ObstacleInstance& obstacle : kObstacles)
    {
        CollisionObject& collisionObject = Collisions::AllocateObject();
        const ObstacleTypeDef& obstacleType = kObstacleTypeDefs[(int)obstacle.m_type];

        modelToWorld.setTranslation(obstacle.m_position);
        // Configure the collision object for tank collisions first
        uint mask = (obstacleType.m_tankCollisionRadius == obstacleType.m_projectileCollisionRadius) ?
                    kCollisionMaskTankObstacle | kCollisionMaskProjectileObstacle :
                    kCollisionMaskTankObstacle;
        collisionObject.Configure(modelToWorld, obstacleType.m_tankCollisionRadius, mask);
        if((obstacleType.m_tankCollisionRadius != obstacleType.m_projectileCollisionRadius) && 
           (obstacleType.m_projectileCollisionRadius > 0))
        {
            // Need a separate collision object for projectiles
            CollisionObject& projectileCollisionObject = Collisions::AllocateObject();
            projectileCollisionObject.Configure(modelToWorld, obstacleType.m_projectileCollisionRadius, kCollisionMaskProjectileObstacle, obstacleType.m_surfaceAngle);
        }
    }
}

void Obstacles::Draw(DisplayList& displayList, const Camera& camera)
{
    FixedTransform3D modelToWorld[kNumObstacleTypes];
    for(uint i = 0; i < kNumObstacleTypes; ++i)
    {
        modelToWorld[i] = kObstacleTypeDefs[i].m_modelToWorld;
    }
    for(const ObstacleInstance& obstacle : kObstacles)
    {
        Intensity intensity = calcIntensity(camera, obstacle.m_position);
        if(intensity > 0)
        {
            modelToWorld[(uint) obstacle.m_type].setTranslation(obstacle.m_position);
            GetFixedShape(kObstacleTypeDefs[(uint) obstacle.m_type].m_shape).Draw(displayList, modelToWorld[(uint) obstacle.m_type], camera, intensity);
        }
    }
}
