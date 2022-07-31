//
//  Component.cpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/13.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
    : mOwner(owner)
    , mUpdateOrder(updateOrder)
{
    // Actorのコンポーネント配列に自身を挿入
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
    // nothing...
}
