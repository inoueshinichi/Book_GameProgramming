//
//  FPSActor.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#include "FPSActor.hpp"
#include "MoveComponent.hpp"
#include "SDL2/SDL_scancode.h"
#include "Renderer.hpp"
#include "AudioSystem.hpp"
#include "Game.hpp"
#include "AudioComponent.hpp"
#include "FPSCamera.hpp"
#include "MeshComponent.hpp"

FPSActor::FPSActor(class Game* game)
    : Actor(game)
{
    mMoveComp = new MoveComponent(this);
    mAudioComp = new AudioComponent(this);
    mLastFootstep = 0.0f;
    mFootstep = mAudioComp->PlayEvent("event:/Footstep");
    mFootstep.SetPaused(true);
    
    mCameraComp = new FPSCamera(this);
    
    // 一人称モデル. FPSActorのyawとFPSCameraのpitchで回転する
    mFPSModel = new Actor(game);
    mFPSModel->SetScale(0.75f);
    mMeshComp = new MeshComponent(mFPSModel);
    mMeshComp->SetMesh(game->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Rifle.gpmesh"));
}

FPSActor::~FPSActor()
{}

void FPSActor::ActorInput(const uint8_t *keyState)
{
    float forwardSpeed = 0.0f;
    float strafeSpeed = 0.0f;
    
    // [w][a][s][d] movement
    if (keyState[SDL_SCANCODE_W])
    {
        forwardSpeed += 400.0f;
    }
    if (keyState[SDL_SCANCODE_S])
    {
        forwardSpeed -= 400.0f;
    }
    if (keyState[SDL_SCANCODE_A])
    {
        strafeSpeed -= 400.0f;
    }
    if (keyState[SDL_SCANCODE_D])
    {
        strafeSpeed += 400.0f;
    }
    
    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetStrafeSpeed(strafeSpeed);
    
    // Mouse movement
    // Get relative movement from SDL2
    int x,y;
    SDL_GetRelativeMouseState(&x, &y);
    // Assume mouse movement is usually between -500 and +500
    const int maxMouseSpeed = 500;
    // Rotation/sec at maximum speed
    const float maxAngularSpeed = Math::Pi * 8;
    float angularSpeed = 0.0f;
    if (x != 0)
    {
        // Convert to およそ[-1.0,1.0]
        angularSpeed = static_cast<float>(x) / maxMouseSpeed;
        // Multiply by rotation/sec
        angularSpeed *= maxAngularSpeed;
    }
    mMoveComp->SetAngularSpeed(angularSpeed);
    
    
    // Compute pitch
    const float maxPitchSpeed = Math::Pi * 8;
    float pitchSpeed = 0.0f;
    if (y != 0)
    {
        // Convert to およそ[-1.0, 1.0]
        pitchSpeed = static_cast<float>(y) / maxPitchSpeed;
        pitchSpeed *= maxPitchSpeed;
    }
    mCameraComp->SetPitchSpeed(pitchSpeed);
}

void FPSActor::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    // Play the footstep if we're moving and haven't recently
    mLastFootstep -= deltaTime;
    if (!Math::NearZero(mMoveComp->GetForwardSpeed()) && mLastFootstep <= 0.0f)
    {
        mFootstep.SetPaused(false);
        mFootstep.Restart();
        mLastFootstep = 0.5f;
    }
    
    // 1人称モデルはFPSActorとの相対位置により更新
    const Vector3 modelOffset(Vector3(10.0f, 10.0f, -10.0f));
    Vector3 modelPos = GetPosition();
    modelPos += GetForward() * modelOffset.x;
    modelPos += GetRight() * modelOffset.y;
    modelPos.z += modelOffset.z;
    mFPSModel->SetPosition(modelPos);
    
    // FPSActorの回転で初期化
    Quaternion q = GetRotation();
    
    // FPSCameraのピッチで回転を更新
    q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCameraComp->GetPitch()));
    mFPSModel->SetRotation(q);
}

void FPSActor::SetFootstepSurface(float value)
{
    // Pause here because the way I setup the parameter in FMOD
    // chaning it will play a footstep
    mFootstep.SetPaused(true);
    mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
    mMeshComp->SetVisible(visible);
}
