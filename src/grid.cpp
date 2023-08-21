// Infinite grid ground plane for Space Tanks.
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

#include "grid.h"
#include "extras/shapes3d.h"
#include "spacetanks.h"

static constexpr int kNumPointsOnEdge = 33;
static constexpr float kGridSpacingFloat = 1.f;
static constexpr StandardFixedTranslationScalar kGridSpacing = kGridSpacingFloat;
static constexpr StandardFixedTranslationScalar kRecipGridSpacing = 1.f / kGridSpacingFloat;

static constexpr int kTotalNumPoints = (kNumPointsOnEdge - 1) * 4;
static constexpr int kTotalNumEdges = kNumPointsOnEdge * 2;
static constexpr float kMinIntensity = 0.1f;
static constexpr float kMaxIntensity = 1.f;

static StandardFixedTranslationVector s_points[kTotalNumPoints];
static Shape3D::Edge s_edges[kTotalNumEdges] = { {0, 1}, {1, 3}, {3, 2}, {2, 0} };
static Intensity s_edgeIntensities[kTotalNumEdges] = {kMinIntensity, kMinIntensity, kMinIntensity, kMinIntensity};

static Shape3D s_grid;

static FixedTransform3D s_gridToView;


void Grid::Init()
{
    StandardFixedTranslationScalar halfEdgeLength = (kGridSpacing * (kNumPointsOnEdge - 1)) * 0.5f;

    // Do the corners first
    s_points[0] = StandardFixedTranslationVector(-halfEdgeLength, 0, -halfEdgeLength);
    s_points[1] = StandardFixedTranslationVector( halfEdgeLength, 0, -halfEdgeLength);
    s_points[2] = StandardFixedTranslationVector(-halfEdgeLength, 0,  halfEdgeLength);
    s_points[3] = StandardFixedTranslationVector( halfEdgeLength, 0,  halfEdgeLength);
    const int kStartX0 = 4;
    const int kStartX1 = kStartX0 + kNumPointsOnEdge - 2;
    const int kStartZ0 = kStartX1 + kNumPointsOnEdge - 2;
    const int kStartZ1 = kStartZ0 + kNumPointsOnEdge - 2;
    static_assert((kStartZ1 + kNumPointsOnEdge - 2) == kTotalNumPoints, "");
    const int kStartE0 = 4;
    const int kStartE1 = 4 + kNumPointsOnEdge - 2;
    static_assert((kStartE1 + kNumPointsOnEdge - 2) == kTotalNumEdges, "");
    const float midPoint = float(kNumPointsOnEdge-1) * 0.5f;
    const float recipMidPoint = 1.f / midPoint;
    for(int i = 0; i < (kNumPointsOnEdge-2); ++i)
    {
        const StandardFixedTranslationScalar p = -halfEdgeLength + (kGridSpacing * (i + 1));
        s_points[kStartX0 + i] = StandardFixedTranslationVector(p, 0, -halfEdgeLength);
        s_points[kStartX1 + i] = StandardFixedTranslationVector(p, 0,  halfEdgeLength);
        s_points[kStartZ0 + i] = StandardFixedTranslationVector(-halfEdgeLength, 0, p);
        s_points[kStartZ1 + i] = StandardFixedTranslationVector( halfEdgeLength, 0, p);
        int edgeOrder = i & 1;
        s_edges[kStartE0 + i][edgeOrder & 1]       = kStartX0 + i;
        s_edges[kStartE0 + i][(edgeOrder + 1) & 1] = kStartX1 + i;
        s_edges[kStartE1 + i][edgeOrder & 1]       = kStartZ0 + i;
        s_edges[kStartE1 + i][(edgeOrder + 1) & 1] = kStartZ1 + i;
        float z = midPoint - (i + 1);
        z = (z < 0.f) ? -z : z;
        z = 1.f - (z * recipMidPoint);
        Intensity intensity = (z * (kMaxIntensity - kMinIntensity)) + kMinIntensity;
        s_edgeIntensities[kStartE0 + i] = intensity;
        s_edgeIntensities[kStartE1 + i] = intensity;
    }

    s_grid.Init(s_points, (uint) kTotalNumPoints, s_edges, s_edgeIntensities, (uint) kTotalNumEdges);
    s_gridToView.setAsIdentity();
}

void Grid::Draw(DisplayList& displayList,const Camera& camera)
{
    // Set the grid's XY position to be a quantized version of the camera position
    StandardFixedTranslationVector origin = camera.GetPosition();
    origin.x = Round(origin.x * kRecipGridSpacing) * kGridSpacing;
    origin.y = 0;
    origin.z = Round(origin.z * kRecipGridSpacing) * kGridSpacing;
    s_gridToView.setTranslation(origin);
    s_grid.Draw(displayList, s_gridToView, camera, kIntensityAdjustment * 0.25f);
}
