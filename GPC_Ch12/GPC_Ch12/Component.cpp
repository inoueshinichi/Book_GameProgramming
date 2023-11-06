//
//  Component.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
    : mOwner(owner)
    , mUpdateOrder(updateOrder)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveCompoent(this);
}

void Component::Update(float deltaTime)
{}


