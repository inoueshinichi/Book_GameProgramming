//
//  InputComponent.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "InputComponent.hpp"
#include "Actor.hpp"

InputComponent::InputComponent(class Actor* owner)
    : MoveComponent(owner)
    , mForwardKey(0)
    , mBackKey(0)
    , mClockwiseKey(0)
    , mCounterClockwiseKey(0)
{}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
    float forwardSpeed = 0.0f;
    if (keyState[mForwardKey])
    {
        forwardSpeed += mMaxForwardSpeed;
    }
    if (keyState[mBackKey])
    {
        forwardSpeed -= mMaxForwardSpeed;
    }
    SetForwardSpeed(forwardSpeed);
    
    float angularSpeed = 0.0f;
    if (keyState[mClockwiseKey])
    {
        angularSpeed += mMaxAngularSpeed;
    }
    if (keyState[mCounterClockwiseKey])
    {
        angularSpeed -= mMaxAngularSpeed;
    }
    SetAngularSpeed(angularSpeed);
}
