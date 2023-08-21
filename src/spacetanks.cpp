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

#include "picovectorscope.h"
#include "extras/shapes3d.h"

#include "spacetanks.h"
#include "shapes.h"
#include "grid.h"
#include "background.h"
#include "collisions.h"
#include "player.h"
#include "obstacles.h"
#include "enemytanks.h"
#include "projectiles.h"
#include "particles.h"
#include "radar.h"

static LogChannel s_spaceTanksLog(false);

class SpaceTanks : public Demo
{
public:
    SpaceTanks() : Demo(0, kFramesPerSecond.getIntegerPart()) {}
    void UpdateAndRender(DisplayList& displayList, float dt);
    void Start()
    {
        Collisions::Reset();
        Grid::Init();
        Obstacles::Init();
        Player::Reset();
        EnemyTanks::Reset();
        Projectiles::Reset();
        Particles::Reset();
        Radar::Reset();
    }
};
static SpaceTanks s_spaceTanks;

void SpaceTanks::UpdateAndRender(DisplayList& displayList, float dt)
{
    Player::Update();
    EnemyTanks::Update();
    Projectiles::Update();
    Particles::Update();
    Radar::Update();
    const Camera& camera = Player::GetCamera();

    Player::Draw(displayList);
    EnemyTanks::Draw(displayList, camera);
    Projectiles::Draw(displayList, camera);
    Particles::Draw(displayList, camera);
    Obstacles::Draw(displayList, camera);
    Grid::Draw(displayList, camera);
    Background::Draw(displayList, camera);
    Radar::Draw(displayList, camera);
}
