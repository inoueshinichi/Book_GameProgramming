//
//  FPSCamera.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef FPSCamera_hpp
#define FPSCamera_hpp

#include "CameraComponent.hpp"

class FPSCamera : public CameraComponent
{
public:
    FPSCamera(class Actor* owner);
    ~FPSCamera() {}
    
    void Update(float deltaTime) override;
    
    float GetPitch() const { return mPitch; }
    float GetPitchSpeed() const { return mPitchSpeed; }
    float GetMaxPit() const { return mMaxPitch; }
    
    void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
    void SetMaxPitch(float pitch) { mMaxPitch = pitch; }
    
private:
    // Rotation/sec speed of pitch
    float mPitchSpeed;
    // Maximum pitch deviation from forward
    float mMaxPitch;
    // Current pitch
    float mPitch;
};

#endif /* FPSCamera_hpp */
