//
//  CircleComponent.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
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


/* 円による衝突判定 */
bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // Calculate distance squared
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    // Calculate sum of radii squared
    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}
