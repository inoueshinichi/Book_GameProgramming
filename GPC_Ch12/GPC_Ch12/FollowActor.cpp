//
//  FollowActor.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "FollowActor.hpp"
#include "SkeletalMeshComponent.hpp"
#include "Game.hpp"
#include "Renderer.hhp"
#include "FollowCamera.hpp"
#include "MoveComponent.hpp"

FollowActor::FollowActor(Game* game)
    : Actor(game)
    , mMoving(false)
{
    mMeshComp = new SkeletalMeshComponent(this);
    mMeshComp->SetMesh(game->GetRenderer()->GetMesh(ASSETS_DIR "Assets/CatWarrior.gpmesh"));
    mMeshComp->SetSkeleton(game->GetSkeleton(ASSETS_DIR
        "Assets/CatWarrior.gpskel"));
    mMeshComp->PlayAnimation(game->GetAnimation(ASSETS_DIR
        "Assets/CatActionIdle.gpanim"));
    SetPosition(Vector3(0.0f, 0.0f, -100.0f));
    
    mMoveComp = new MoveComponent(this);
    mCameraComp = new FollowCamera(this);
    mCameraComp->SnapToIdeal();
}

void FollowActor::ActorInput(const uint8_t* keys)
{
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    
    // W A S D movement
    if (keys[SDL_SCANCODE_W])
    {
        forwardSpeed += 400.0f;
    }
    
    if (keys[SDL_SCANCODE_S])
    {
        forwardSpeed -= 400.0f;
    }
    
    if (keys[SDL_SCANCODE_A])
    {
        angularSpeed -= Math::Pi;
    }
    
    if (keys[SDL_SCANCODE_D])
    {
        angularSpeed += Math::Pi;
    }
    
    // Did we just start moving?
    if (!mMoving && !Math::NearZero(forwardSpeed))
    {
        mMoving = true;
        mMeshComp->PlayAnimation(GetGame()->GetAnimation(ASSETS_DIR "Assets/CatRunSprint.gpanim"), 1.25f);
    }
    // or did we just stop moving?
    else if (mMoving && Math::NearZero(forwardSpeed))
    {
        mMoving = false;
        mMeshComp->PlayAnimation(GetGame()->GetAnimation(ASSETS_DIR "Assets/CatActionIdle.gpanim"));
    }
    
    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetAngularSpeed(angularSpeed);
}

void FollowActor::SetVisible(bool visible)
{
    mMeshComp->SetVisible(visible);
}


