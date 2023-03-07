//
//  FollowCamera.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#include "FollowCamera.hpp"
#include "Actor.hpp"
#include "Math.hpp"

FollowCamera::FollowCamera(class Actor* owner)
    : CameraComponent(owner)
    , mHorzDist(350.0f)
    , mVertDist(150.0f)
    , mTargetDist(100.0f)
    , mSpringConstant(64.0f)
{}

Vector3 FollowCamera::ComputeCameraPos() const
{
    // カメラの位置を所有アクターの上後方にセット
    Vector3 cameraPos = mOwner->GetPosition();
    cameraPos -= mOwner->GetForward() * mHorzDist;
    cameraPos += Vector3::UnitZ * mVertDist;
    return cameraPos;
}

void FollowCamera::SnapToIdeal()
{
    mActualPos = ComputeCameraPos();
    
    mVelocity = Vector3::Zero;
    
    Vector3 target = mOwner->GetPosition() +
                mOwner->GetForward() * mTargetDist;
    
    // カメラは反転しないので, 上方ベクトルはZ軸の基本ベクトルのまま
    Matrix4 view = Matrix4::CreateLookAt(mActualPos,
                                         target,
                                         Vector3::UnitZ);

    SetViewMatrix(view);
}

void FollowCamera::Update(float deltaTime)
{
    /**
     バネなし追従カメラ
    */
//    CameraComponent::Update(deltaTime);
//
//    // ターゲットは所有アクターから前方に離れた座標
//    Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;
//
//    // カメラは反転しないので, 上方ベクトルはZ軸の基本ベクトルのまま
//    Matrix4 view = Matrix4::CreateLookAt(ComputeCameraPos(), target, Vector3::UnitZ);
//
//    SetViewMatrix(view);
    
    /**
    バネあり追従カメラ
    */
    
    CameraComponent::Update(deltaTime);
    
    // 理想のカメラ位置
    Vector3 idealPos = ComputeCameraPos();
    
    // ばね定数から減衰を計算
    float dampening = 2.0f * Math::Sqrt(mSpringConstant);
    
    // 実際と理想の差を計算
    Vector3 diff = mActualPos - idealPos;
    
    // ばねによる加速度の計算 (mVelocityは前フレームの速度)
    Vector3 acel = -mSpringConstant * diff - dampening * mVelocity;
    
    // 速度の更新
    mVelocity += acel * deltaTime;
    
    // 実際のカメラポジションを更新
    mActualPos += mVelocity * deltaTime;
    
    // ターゲットの位置
    Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;
    
    // 実際のカメラポジションで注視行列を作成
    Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
    SetViewMatrix(view);
    
    
}




