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

#include "shapes.h"

static LogChannel s_spaceTanksLog(false);

class Player
{
public:
    void Reset()
    {
        m_position = StandardFixedTranslationVector(4,0.5,0);
        m_yaw = kPi * 1.5f;
    }

    void UpdateAndRender(DisplayList& displayList)
    {
        (void) displayList;
        // Handle the rotate left and y buttons
        if(Buttons::IsHeld(Buttons::Id::Left))
        {
            m_yaw -= kRotationSpeed;
            if(m_yaw < 0) m_yaw += kPi * 2.f;
        }
        if(Buttons::IsHeld(Buttons::Id::Right))
        {
            m_yaw += kRotationSpeed;
            if(m_yaw > kPi * 2.f) m_yaw -= kPi * 2.f;
        }

        // Construct the rotation part of the viewToWorld transform
        FixedTransform3D viewToWorld;
        viewToWorld.setRotationXYZ(0, m_yaw, 0);

        // Handle the drive button
        if(Buttons::IsHeld(Buttons::Id::Thrust))
        {
            m_position += (StandardFixedTranslationVector)viewToWorld.m[2] * kTranslationSpeed;
            m_position.y = 0.6875f;
        }

        // Set the translation part of the viewToWorld transform
        viewToWorld.setTranslation(m_position);
        // Invert to make the worldToView transform that we can use for the camera
        viewToWorld.orthonormalInvert(m_worldToView);
    }

    const FixedTransform3D& GetWorldToView() const { return m_worldToView; }
private:
    static constexpr SinTable::Index kRotationSpeed = 0.02f;
    static constexpr SinTable::Index kTranslationSpeed = 0.02f;
    StandardFixedTranslationVector   m_position;
    SinTable::Index                  m_yaw;
    FixedTransform3D                 m_worldToView;
};
static Player s_player;

class SpaceTanks : public Demo
{
public:
    SpaceTanks() : Demo(0, 60) {}
    void UpdateAndRender(DisplayList& displayList, float dt);
    void Start() {s_player.Reset();}
};
static SpaceTanks s_spaceTanks;


void SpaceTanks::UpdateAndRender(DisplayList& displayList, float dt)
{
    s_player.UpdateAndRender(displayList);

    FixedTransform3D tankToWorld;
    tankToWorld.setRotationXYZ(0, 0, 0);
    tankToWorld.setTranslation(StandardFixedTranslationVector(0, 0, 0));
    GetFixedShape(FixedShape::BasicTank).Draw(displayList, tankToWorld, s_player.GetWorldToView(), 0.8f);

    FixedTransform3D gridModelToWorld;
    gridModelToWorld.setAsIdentity();
    gridModelToWorld.setTranslation(StandardFixedTranslationVector(-3.5, 0, -3.5));
    GetFixedShape(FixedShape::GridXZ8x8).Draw(displayList, gridModelToWorld, s_player.GetWorldToView(), 0.4f);

}
