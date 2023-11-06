//
//  BallActor.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "BallActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"
#include "Mesh.hpp"
#include "BallActor.hpp"
#include "AudioComponent.hpp"

BallActor::BallActor(Game* game)
    : Actor(game)
    , mLifeSpan(2.0f)
{
    // SetScale(1.0f);
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = GetGame()->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Sphere.gpmesh");
    mc->SetMesh(mesh);
    mMyMove = new BallMove(this);
    mMyMove->SetForwardSpeed(1500.0f);
    mAudioComp = new AudioComponent(this);
}

void BallActor::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    mLifeSpan -= deltaTime;
    if (mLifeSpan < 0.0f)
    {
        SetState(EDead);
    }
}

void BallActor::SetPlayer(Actor* player)
{
    mMyMove->SetPlayer(player);
}

void BallActor::HitTarget()
{
    mAudioComp->PlayEvent("event:/Ding");
}
