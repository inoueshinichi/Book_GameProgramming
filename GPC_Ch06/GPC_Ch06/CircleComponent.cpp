//
//  CircleComponent.cpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/14.
//

#include "CircleComponent.hpp"
#include "Actor.hpp"

CircleComponent::CircleComponent(class Actor* owner)
    : Component(owner)
    , mRadius(0.0f)
{
    
}

const Vector3& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // Calculate distance squared
    Vector3 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    // Calculate sum of radii squared
    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}
