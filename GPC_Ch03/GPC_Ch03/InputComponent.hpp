//
//  InputComponent.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/19.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "MoveComponent.hpp"
#include <cstdint>

class Actor;

class InputComponent : public MoveComponent
{
public:
    InputComponent(Actor* owner);
    
    void ProcessInput(const uint8_t* keyState) override;
    
    float GetMaxForward() const { return mMaxForwardSpeed; }
    float GetMaxAngular() const { return mMaxAngularSpeed; }
    int GetForwardKey() const { return mForwardKey; }
    int GetBackKey() const { return mBackKey; }
    int GetClockwiseKey() const { return mClockwiseKey; }
    int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }
    
    void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
    void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
    void SetForwardKey(int key) { mForwardKey = key; }
    void SetBackKey(int key) { mBackKey = key; }
    void SetClockwiseKey(int key) { mClockwiseKey = key; }
    void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
    
private:
    float mMaxForwardSpeed;
    float mMaxAngularSpeed;
    int mForwardKey;
    int mBackKey;
    int mClockwiseKey;
    int mCounterClockwiseKey;
};

#endif /* InputComponent_hpp */
