//
//  FPSCamera.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#include "FPSCamera.hpp"
#include "Actor.hpp"

FPSCamera::FPSCamera(class Actor* owner)
    : CameraComponent(owner)
    , mPitchSpeed(0.0f)
    , mMaxPitch(Math::Pi/3.0f)
    , mPitch(0.0f)
{}

void FPSCamera::Update(float deltaTime)
{
    // 親クラスのUpdateを呼び出す(今は何もしない)
    CameraComponent::Update(deltaTime);
    
    // カメラの位置は所有アクターの位置
    Vector3 cameraPos = mOwner->GetPosition();
    
    // ピッチの角速度に基づいてピッチを更新
    mPitch += mPitchSpeed * deltaTime;
    // ピッチを[-max,+max]の範囲に収める
    mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
    // ピッチ回転を表すクォータニオンを作る
    Quaternion q(mOwner->GetRight(), mPitch);
    
    // ピッチのクォータニオンで, 所有アクターの前方ベクトルを回転
    Vector3 viewForward = Vector3::Transform(mOwner->GetForward(), q);
    
    // ターゲットの位置は所有アクターの前方100単位
    Vector3 target = cameraPos + /*mOwner->GetForward()*/ viewForward * 100.0f;
    
    // 上方ベクトルもピッチのクォータニオンで回転
    Vector3 up = /*Vector3::UnitZ;*/ Vector3::Transform(Vector3::UnitZ, q);
    // 注視行列を作ってビューに反映する
    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
    SetViewMatrix(view);
}



