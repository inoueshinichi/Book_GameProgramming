//
//  CircleComponent.cpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/19.
//

#include "CircleComponent.hpp"
#include "Actor.hpp"

CircleComponent::CircleComponent(Actor* owner)
    : Component(owner)
    , mRadius(0.0f)
{}

const Vector2& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}


bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // 距離の2乗を計算
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();
    
    // 2つの円の半径の和の2乗を計算
    float raddiSq = a.GetRadius() + b.GetRadius();
    raddiSq *= raddiSq;
    
    return distSq <= raddiSq;
}
