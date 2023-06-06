//
//  MoveComponent.cpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder)
    , mAngularSpeed(0.0f)
    , mForwardSpeed(0.0f)
{}

void MoveComponent::Update(float deltaTime)
{
    /* 必ず回転更新, 並進更新の順序で行う */
    
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = mOwner->GetRotation();
        float angle = mAngularSpeed * deltaTime;
        
        // up axis only
        Quaternion inc(Vector3::UnitZ, angle);
        rot = Quaternion::Concatenate(rot, inc);
        mOwner->SetRotation(rot);
    }
    
    if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
    {
        Vector3 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}


