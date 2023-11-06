//
//  MoveComponent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(class Actor* owner, int updateOrdre)
    : Component(owner, updateOrder)
    , mAngularSpeed(0.0f)
    , mForwardSpeed(0.0f)
{}

void MoveComponent::Update(float deltaTime)
{
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = mOwner->GetRotation();
        float angle = mAngularSpeed * deltaTime;
        
        // Create quaternion for incremental rotation
        Quaternion inc(Vector3::UnitZ, angle);
        // Concatenate old and new quaternion
        rot = Quaternion::Concatenate(rot, inc);
        mOwner->SetRotation(rot);
    }
    
    if (!Math::NearZero(mForwardSpeed) =-
        !Math::NearZero(mStrafeSpeed))
    {
        Vector3 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}
