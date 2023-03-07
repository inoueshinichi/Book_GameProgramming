//
//  FollowCamera.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef FollowCamera_hpp
#define FollowCamera_hpp

#include "CameraComponent.hpp"

class FollowCamera : public CameraComponent
{
public:
    FollowCamera(class Actor* owner);
    ~FollowCamera() {}
    
    void SetHorzDist(float dist) { mHorzDist = dist; }
    void SetVertDist(float dist) { mVertDist = dist; }
    void SetTargetDist(float dist) { mTargetDist = dist; }
    
    void Update(float deltaTime) override;
    
    void SnapToIdeal();
private:
    Vector3 ComputeCameraPos() const;
    
    float mHorzDist;
    float mVertDist;
    float mTargetDist;
    
    float mSpringConstant;
    Vector3 mActualPos; // 実際のカメラ位置(バネカメラ)
    Vector3 mVelocity;  // 実際のカメラの速度(バネカメラ)
};

#endif /* FollowCamera_hpp */
