//
//  BoxComponent.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#include "BoxComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "PhysWorld.hpp"

BoxComponent::BoxComponent(Actor* owner,
                           int updateOrder)
    : Component(owner, updateOrder)
    , mObjectBox(Vector3::Zero, Vector3::Zero)
    , mWorldBox(Vector3::Zero, Vector3::Zero)
    , mShouldRotate(true)
{
    mOwner->GetGame()->GetPhysWorld()->AddBox(this);
}

BoxComponent::~BoxComponent()
{
    mOwner->GetGame()->GetPhysWorld()->RemoveBox(this);
}

void BoxComponent::OnUpdateWorldTransform()
{
    // Reset to object space box
    mWorldBox = mObjectBox;
    
    // Scale
    mWorldBox.mMin *= mOwner->GetScale();
    mWorldBox.mMax *= mOwner->GetScale();
    
    // Rotate (if we want to)
    if (mShouldRotate)
    {
        mWorldBox.Rotate(mOwner->GetRotation());
    }
    
    // Translate
    mWorldBox.mMin += mOwner->GetPosition();
    mWorldBox.mMax += mOwner->GetPosition();
}
