// Space Tanks work-in-progress
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

typedef FixedPoint<8, 8, int32_t, int32_t> FrameRateValue;
typedef FixedPoint<4, 16, int32_t, int32_t, false> Angle;

// The frame rate to run at
static constexpr FrameRateValue kFramesPerSecond = 240;

// Convert from something per second to something per frame
static constexpr FrameRateValue kPerSecondMultiplier = 1.f / (float) kFramesPerSecond;

// Adjustment to try to keep intensities uniform across different frame rates
// TODO: Make this better.  It doesn't account for intensity non-linearity.
static constexpr Intensity kIntensityAdjustment = 120.f / (float) kFramesPerSecond;
