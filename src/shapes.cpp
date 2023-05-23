// 3D shapes for Space Tanks.
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

#include "shapes.h"
#include "picovectorscope.h"

static constexpr StandardFixedTranslationVector kUnitCubePoints[] = {
    StandardFixedTranslationVector(-1, -1, -1),
    StandardFixedTranslationVector( 1, -1, -1),
    StandardFixedTranslationVector(-1,  1, -1),
    StandardFixedTranslationVector( 1,  1, -1),
    StandardFixedTranslationVector(-1, -1,  1),
    StandardFixedTranslationVector( 1, -1,  1),
    StandardFixedTranslationVector(-1,  1,  1),
    StandardFixedTranslationVector( 1,  1,  1),
};

static constexpr uint16_t kUnitCubeEdges[][2] = {
    {0, 1}, {1, 3}, {3, 2}, {2, 0},
    {0, 4},
    {4, 5}, {5, 7}, {7, 6}, {6, 4},
    {1, 5}, {3, 7}, {2, 6},
};

static constexpr StandardFixedTranslationVector kBasicTankPoints[] = {
    StandardFixedTranslationVector(-0.5f, 0, -1),
    StandardFixedTranslationVector( 0.5f, 0, -1),
    StandardFixedTranslationVector(-0.5f, 0,  1),
    StandardFixedTranslationVector( 0.5f, 0,  1),
    StandardFixedTranslationVector(-0.5f, 1, -1),
    StandardFixedTranslationVector( 0.5f, 1, -1),
    StandardFixedTranslationVector(-0.0625f, 0.75f, -0.5f),  // 6
    StandardFixedTranslationVector(-0.0625f, 0.75f, 0.5f),   // 7
    StandardFixedTranslationVector( 0.0625f, 0.75f, -0.5f),  // 8
    StandardFixedTranslationVector( 0.0625f, 0.75f, 0.5f),   // 9
    StandardFixedTranslationVector(-0.0625f, 0.625f, -0.25f),// 10
    StandardFixedTranslationVector(-0.0625f, 0.625f, 0.5f),  // 11
    StandardFixedTranslationVector( 0.0625f, 0.625f, -0.25f),// 12
    StandardFixedTranslationVector( 0.0625f, 0.625f, 0.5f),  // 13
};

static constexpr uint16_t kBasicTankEdges[][2] = {
    {2, 0}, {0, 1}, {1, 3}, {3, 2}, // Base
    {2, 4}, {4, 5}, {5, 3}, // Wedge front
    {0, 4}, {1, 5}, // Verticals
    {6, 7}, {7, 9}, {9, 8},
    {10, 11}, {11, 13}, {13, 12},
    {7, 11}, {9, 13},
};

static constexpr StandardFixedTranslationVector kGridXZ8x8Points[] = {
    StandardFixedTranslationVector(0, 0, 0),
    StandardFixedTranslationVector(1, 0, 0),
    StandardFixedTranslationVector(2, 0, 0),
    StandardFixedTranslationVector(3, 0, 0),
    StandardFixedTranslationVector(4, 0, 0),
    StandardFixedTranslationVector(5, 0, 0),
    StandardFixedTranslationVector(6, 0, 0),
    StandardFixedTranslationVector(7, 0, 0),
    StandardFixedTranslationVector(0, 0, 7),
    StandardFixedTranslationVector(1, 0, 7),
    StandardFixedTranslationVector(2, 0, 7),
    StandardFixedTranslationVector(3, 0, 7),
    StandardFixedTranslationVector(4, 0, 7),
    StandardFixedTranslationVector(5, 0, 7),
    StandardFixedTranslationVector(6, 0, 7),
    StandardFixedTranslationVector(7, 0, 7),
    StandardFixedTranslationVector(0, 0, 0),
    StandardFixedTranslationVector(0, 0, 1),
    StandardFixedTranslationVector(0, 0, 2),
    StandardFixedTranslationVector(0, 0, 3),
    StandardFixedTranslationVector(0, 0, 4),
    StandardFixedTranslationVector(0, 0, 5),
    StandardFixedTranslationVector(0, 0, 6),
    StandardFixedTranslationVector(0, 0, 7),
    StandardFixedTranslationVector(7, 0, 0),
    StandardFixedTranslationVector(7, 0, 1),
    StandardFixedTranslationVector(7, 0, 2),
    StandardFixedTranslationVector(7, 0, 3),
    StandardFixedTranslationVector(7, 0, 4),
    StandardFixedTranslationVector(7, 0, 5),
    StandardFixedTranslationVector(7, 0, 6),
    StandardFixedTranslationVector(7, 0, 7),
};

static constexpr uint16_t kGridXZ8x8Edges[][2] = {
    {0, 8}, {1, 9}, {2, 10}, {3, 11}, {4, 12}, {5, 13}, {6, 14}, {7, 15},
    {16, 24}, {17, 25}, {18, 26}, {19, 27}, {20, 28}, {21, 29}, {22, 30}, {23, 31},
};

constexpr Shape3D kFixedShapes[]
{
    SHAPE_3D(kUnitCubePoints, kUnitCubeEdges),
    SHAPE_3D(kBasicTankPoints, kBasicTankEdges),
    SHAPE_3D(kGridXZ8x8Points, kGridXZ8x8Edges),
};
static_assert((sizeof(kFixedShapes) / sizeof(kFixedShapes[0])) == (size_t) FixedShape::Count, "");

