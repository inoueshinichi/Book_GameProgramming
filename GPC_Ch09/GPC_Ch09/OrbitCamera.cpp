//
//  OrbitCamera.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/02/28.
//

#include "OrbitCamera.hpp"
#include "Actor.hpp"

OrbitCamera::OrbitCamera(Actor* owner)
    : CameraComponent(owner)
    , mOffset(-400.0f, 0.0f, 400.0f)
    , mUp(Vector3::UnitZ)
    , mPitchSpeed(0.0f)
    , mYawSpeed(0.0f)
{
    
}

void OrbitCamera::Update(float deltaTime)
{
    CameraComponent::Update(deltaTime);
    
    // ワールド上方を軸とするヨーのクォータニオンを作成
    Quaternion yaw(Vector3::UnitZ, mYawSpeed * deltaTime);
    
    // カメラのオフセット(xyz)と上方ベクトルをヨーで変換
    mOffset = Vector3::Transform(mOffset, yaw);
    mUp = Vector3::Transform(mUp, yaw);
    
    // カメラの前方と右方を計算する
    // 前方はowner.position - (owner.position + offset) = -offset
    Vector3 forward = -1.0f * mOffset;
    forward.Normalize(); // 単位ベクトル化
    // 右方は前方と上方からクロス積で求める
    Vector3 right = Vector3::Cross(mUp, forward);
    right.Normalize(); // 単位ベクトル化
    
    // カメラ右方を軸とするピッチのクォータニオンを作成
    Quaternion pitch(right, mPitchSpeed * deltaTime);
    
    // カメラのオフセットと上方ベクトルをピッチで変換
    mOffset = Vector3::Transform(mOffset, pitch);
    mUp = Vector3::Transform(mUp, pitch);
    
    // 注視行列の作成
    Vector3 target = mOwner->GetPosition();
    Vector3 cameraPos = target + mOffset;
    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, mUp);
    SetViewMatrix(view);
}
