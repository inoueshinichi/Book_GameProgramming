//
//  InputComponent.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "MoveComponent.hpp"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
    InputComponent(class Actor* owner);
    
//    void ProcessInput(const uint8_t* keyState) override;
    void ProcessInput(const struct InputState& state) override;
    
    float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }
    float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
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
