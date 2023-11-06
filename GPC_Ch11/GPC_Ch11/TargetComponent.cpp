//
//  TargetComponent.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#include "TargetComponent.hpp"
#include "BoxComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "PhysWorld.hpp"
#include "Math.hpp"
#include "HUD.hpp"

TargetComponent::TargetComponent(Actor* owner)
    : Component(owner)
{
    mOwner->GetGame()->GetHUD()->AddTargetComponent(this);
}

TargetComponent::~TargetComponent()
{
    mOwner->GetGame()->GetHUD()->RemoveTargetComponent(this);
}
