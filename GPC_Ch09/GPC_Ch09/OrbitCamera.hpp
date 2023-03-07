//
//  OrbitCamera.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/02/28.
//

#ifndef OrbitCamera_hpp
#define OrbitCamera_hpp

#include "CameraComponent.hpp"

/**
 ターゲットを中心とした衛生軌道で動くカメラ
 */

class OrbitCamera : public CameraComponent
{
public:
    OrbitCamera(class Actor* owner);
    ~OrbitCamera() {}
    
    float GetPitchSpeed() const { return mPitchSpeed; }
    float GetYawSpeed() const { return mYawSpeed; }

    void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
    void SetYawSpeed(float speed) { mYawSpeed = speed; }
    
    void Update(float deltaTime) override;
                
private:
    // ターゲットからのオフセット
    Vector3 mOffset;
    // カメラの上方ベクトル
    Vector3 mUp;
    // ピッチの角速度
    float mPitchSpeed;
    // ヨーの角速度
    float mYawSpeed;
};

#endif /* OrbitCamera_hpp */
