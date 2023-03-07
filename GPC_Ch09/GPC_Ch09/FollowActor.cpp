//
//  FollowActor.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/01/25.
//

#include "FollowActor.hpp"
#include "MeshComponent.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "FollowCamera.hpp"
#include "MoveComponent.hpp"

FollowActor::FollowActor(Game* game)
    : Actor(game)
{
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(
                       game->GetRenderer()->GetMesh(ASSETS_DIR "Assets/RacingCar.gpmesh"));
    SetPosition(Vector3(0.0f, 0.0f, -100.0f));
    
    mMoveComp = new MoveComponent(this);
    mCameraComp = new FollowCamera(this);
    mCameraComp->SnapToIdeal(); // 追従カメラの初期化
    
}

void FollowActor::ActorInput(const uint8_t *keyState)
{
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    
    // [w][a][s][d] movement
    if (keyState[SDL_SCANCODE_W])
    {
        forwardSpeed += 500.0f;
    }
    if (keyState[SDL_SCANCODE_S])
    {
        forwardSpeed -= 500.0;
    }
    if (keyState[SDL_SCANCODE_A])
    {
        angularSpeed -= Math::Pi;
    }
    if (keyState[SDL_SCANCODE_D])
    {
        angularSpeed += Math::Pi;
    }
    
    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetAngularSpeed(angularSpeed);
    
    // Adjust horizontal distance of camera based on speed
    if (!Math::NearZero(forwardSpeed))
    {
        mCameraComp->SetHorzDist(500.0f);
    }
    else
    {
        mCameraComp->SetHorzDist(350.0f);
    }
}

void FollowActor::SetVisible(bool visible)
{
    mMeshComp->SetVisible(visible);
}
