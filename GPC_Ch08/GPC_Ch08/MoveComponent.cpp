//
//  MoveComponent.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder)
    , mAngularSpeed(0.0f)
    , mForwardSpeed(0.0f)
{}

MoveComponent::~MoveComponent() {}

void MoveComponent::Update(float deltaTime)
{
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = mOwner->GetRotation();
        rot += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rot);
    }
    
    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        
        /* 小惑星用の画面ラップ(画面の左縁で見切れたものは, 右縁の内側に表示される */
//        if (pos.x < 0.0f) { pos.x = 1022.0f; }
//        else if (pos.x > 1024.0f) { pos.y = 2.0f; }
//        if (pos.y < 0.0f) { pos.y = 766.0f; }
//        else if (pos.y > 768.0f) { pos.y = 2.0f; }
        
        if (pos.x < -512.0f) { pos.x = 510.0f; }
        else if (pos.x > 512.0f) { pos.x = -510.0f; }
        if (pos.y < -384.0f) { pos.y = 382.0f; }
        else if (pos.y > 384.0f) { pos.y = -382.0f; }
        
        mOwner->SetPosition(pos);
    }
}
