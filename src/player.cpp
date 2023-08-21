// Space Tanks Player class
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

#include "player.h"
#include "spacetanks.h"
#include "projectiles.h"
#include "collisions.h"

// Constants
static constexpr Angle kRotationSpeed = 1.0f * (float) kPerSecondMultiplier;
static constexpr Angle kRotationAcceleration = 0.01f * (float) kPerSecondMultiplier;;
static constexpr StandardFixedTranslationScalar kTranslationSpeed = 2.5f * (float) kPerSecondMultiplier;
static constexpr StandardFixedTranslationScalar kAcceleration = 0.02f * (float) kPerSecondMultiplier;

// Module scoped static variables
static Angle   s_yaw;
static Angle   s_yawSpeed;
static StandardFixedTranslationVector   s_position;
static StandardFixedTranslationVector   s_velocity;
static StandardFixedTranslationScalar   s_speed;

// Class scoped static variables
Camera                         Player::s_camera;

LogChannel s_playerLog(true);

void Player::Reset()
{
    s_position = StandardFixedTranslationVector(4,0.5f,0);
    s_yaw = kPi * 1.5f;
}

void Player::Update()
{
    // Handle the rotate left and y buttons
    bool dampYaw = true;
    if(Buttons::IsHeld(Buttons::Id::Left))
    {
        s_yawSpeed -= kRotationAcceleration;
        if(s_yawSpeed < -kRotationSpeed) s_yawSpeed = -kRotationSpeed;
        dampYaw = false;
    }
    if(Buttons::IsHeld(Buttons::Id::Right))
    {
        s_yawSpeed += kRotationAcceleration;
        if(s_yawSpeed > kRotationSpeed) s_yawSpeed = kRotationSpeed;
        dampYaw = false;
    }
    if(dampYaw)
    {
        if(s_yawSpeed > 0)
        {
            s_yawSpeed -= kRotationAcceleration;
            if(s_yawSpeed < 0) s_yawSpeed = 0;
        }
        else
        {
            s_yawSpeed += kRotationAcceleration;
            if(s_yawSpeed > 0) s_yawSpeed = 0;
        }
    }
    s_yaw += s_yawSpeed;
    if(s_yaw < 0) s_yaw += kPi * 2.f;
    if(s_yaw > kPi * 2.f) s_yaw -= kPi * 2.f;

    // Construct the rotation part of the viewToWorld transform
    FixedTransform3D viewToWorld;
    viewToWorld.setRotationXYZ(0, (SinTable::Index) s_yaw, 0);

    // Handle the drive button
    if(Buttons::IsHeld(Buttons::Id::Thrust))
    {
        // Accelerate
        s_speed += kAcceleration;
        if(s_speed > kTranslationSpeed)
        {
            s_speed = (StandardFixedTranslationScalar) kTranslationSpeed;
        }
    }
    else
    {
        // Decelerate
        s_speed -= kAcceleration;
        if(s_speed < 0)
        {
            s_speed = 0;
        }
    }
    s_velocity = (StandardFixedTranslationVector)viewToWorld.m[2] * s_speed;
    s_position += s_velocity;
    s_position.y = 0.625f;

    // Set the translation part of the viewToWorld transform
    viewToWorld.setTranslation(s_position);

    if(Buttons::IsJustPressed(Buttons::Id::Fire) && !Projectiles::IsActive(0))
    {
        // Camera is z into the screen, but tanks are x forward
        FixedTransform3D modelToWorld;
        modelToWorld.markAsManuallyManipulated();
        modelToWorld.m[0] = viewToWorld.m[2];
        modelToWorld.m[1] = viewToWorld.m[1];
        modelToWorld.m[2] = -viewToWorld.m[0];
        // LOG_INFO(s_playerLog, "\n%f, %f, %f\n", (float) modelToWorld.m[0].x, (float) modelToWorld.m[0].y, (float) modelToWorld.m[0].z);
        // LOG_INFO(s_playerLog, "%f, %f, %f\n", (float) modelToWorld.m[1].x, (float) modelToWorld.m[1].y, (float) modelToWorld.m[1].z);
        // LOG_INFO(s_playerLog, "%f, %f, %f\n", (float) modelToWorld.m[2].x, (float) modelToWorld.m[2].y, (float) modelToWorld.m[2].z);
        modelToWorld.t = viewToWorld.t;
        Projectiles::Create(0, modelToWorld, kCollisionMaskProjectileObstacle | kCollisionMaskEnemy);
    }

    // Update the camera
    s_camera.SetCameraToWorld(viewToWorld);
    s_camera.SetTanHalfVerticalFOV(0.5f);
    s_camera.Calculate();
}

void Player::Draw(DisplayList& displayList)
{
    (void) displayList;
}
