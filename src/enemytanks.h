// Space Tanks enemy tank class
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

static constexpr int kMaxEnemyTanks = 4;

// Static class to manage _all_ the enemy tanks
class EnemyTanks
{
public:
    static void Reset();
    static void Update();
    static void Draw(DisplayList& displayList, const Camera& camera);
    static void Destroy(const class CollisionObject& collisionObject);
    // Returns nullptr if the specified tank is not alive
    static const FixedTransform3D* GetTransformIfAlive(int idx);
};