// Space Tanks radar display
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

#include "radar.h"
#include "spacetanks.h"
#include "enemytanks.h"

static constexpr Angle kRadarRotationStep = 1.f * k2Pi * (float) kPerSecondMultiplier;
static constexpr DisplayListVector2 kRadarPos(0.15f, 0.85f);
static constexpr StandardFixedTranslationScalar kRadarRadius = 0.1f;
static constexpr StandardFixedTranslationScalar kAspectRatio = 3.f / 4.f;
static constexpr StandardFixedTranslationScalar kRadarRange = 8.f;
static constexpr StandardFixedTranslationScalar kRadarRange2 = kRadarRange * kRadarRange;
static constexpr StandardFixedTranslationScalar kRadarScale = (float) kRadarRadius / (float) kRadarRange;
static constexpr StandardFixedTranslationScalar kRecip2Pi = 1.f / (float) k2Pi;
static constexpr int kNumCircleSegments = 32;

static DisplayListVector2 s_circlePoints[kNumCircleSegments];

static Angle s_radarAngle = 0;
static StandardFixedTranslationScalar s_normRadarAngle = 0;
LogChannel s_radarLog(true);

static void drawPing(DisplayList& displayList, const FixedTransform3D& worldToView, const StandardFixedTranslationVector& pos)
{
    StandardFixedTranslationVector localPos;
    worldToView.transformVector(localPos, pos);
    StandardFixedTranslationScalar angle = StandardFixedTranslationScalar::ApproxATan2(localPos.x, localPos.z);
    Intensity intensity = ((angle * kRecip2Pi) + 0.5f - s_normRadarAngle).frac();
    StandardFixedTranslationScalar dist2 = (localPos.x * localPos.x) + (localPos.z * localPos.z);
    StandardFixedTranslationScalar scale = kRadarScale;
    if(dist2 > kRadarRange2)
    {
        // Adjust the scale to clamp the blip to the edge of the radar
        StandardFixedTranslationScalar dist = dist2.sqrt();
        scale = kRadarRadius / dist;
        //LOG_INFO(s_radarLog, "%f, %f, %f\n", (float) dist2, (float) dist, (float) scale);
    }
    DisplayListVector2 screenPos(localPos.x * scale * kAspectRatio, localPos.z * scale);
    screenPos += kRadarPos;
    displayList.PushPoint(screenPos, intensity);
}

void Radar::Reset()
{
    s_radarAngle = 0;
    Angle angle;
    for(int i = 0; i < kNumCircleSegments; ++i)
    {
        angle = (Angle) k2Pi * ((float) i / kNumCircleSegments);
        SinTable::ValueType s, c;
        SinTable::SinCos(angle, s, c);
        s_circlePoints[i].x = s * kRadarRadius * kAspectRatio + kRadarPos.x;
        s_circlePoints[i].y = c * -kRadarRadius + kRadarPos.y;
        //LOG_INFO(s_radarLog, "%f, %f\n", (float) s_circlePoints[i].x, (float) s_circlePoints[i].y);
    }
}

void Radar::Update()
{
    s_radarAngle += kRadarRotationStep;
    if(s_radarAngle > k2Pi)
    {
        s_radarAngle -= k2Pi;
    }
    s_normRadarAngle = kRecip2Pi * s_radarAngle;
}

void Radar::Draw(DisplayList& displayList, const Camera& camera)
{
    // Draw the radar sweep
    displayList.PushVector(kRadarPos, 0);
    SinTable::ValueType s, c;
    SinTable::SinCos(s_radarAngle, s, c);
    displayList.PushVector(-s * kRadarRadius * kAspectRatio + kRadarPos.x, c * -kRadarRadius + kRadarPos.y, 1);

    // Draw the circle
    displayList.PushVector(s_circlePoints[kNumCircleSegments - 1], 0);
    for(int i = 0; i < kNumCircleSegments; ++i)
    {
        displayList.PushVector(s_circlePoints[i], 0.5f);
    }


    // Draw all the active enemy tanks
    const FixedTransform3D& cameraToWorld = camera.GetCameraToWorld();
    FixedTransform3D worldToCamera;
    cameraToWorld.orthonormalInvert(worldToCamera);
    for(int i = 0; i < kMaxEnemyTanks; ++i)
    {
        const FixedTransform3D* modelToWorld = EnemyTanks::GetTransformIfAlive(i);
        if(modelToWorld) drawPing(displayList, worldToCamera, modelToWorld->t);
    }
}
