//
//  Component.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(class Actor* owner, int updateOrder)
    : mOwner(owner)
    , mUpdateOrder(updateOrder)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{}
