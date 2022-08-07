//
//  CircleComponent.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "CircleComponent.hpp"
#include "Actor.hpp"

CircleComponent::CircleComponent(class Actor* owner)
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

/* 簡易的な衝突検知(円交差を利用) */
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
