//
//  SplineActor.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/01/14.
//

#include "SplineActor.hpp"
#include "MeshComponent.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "SplineCamera.hpp"
#include "MoveComponent.hpp"

SplineActor::SplineActor(Game* game)
    : Actor(game)
{
    //MeshComponent* mc = new MeshComponent(this);
    //mc->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
    //SetPosition(Vector3(0.0f, 0.0f, -100.0f));
    
    mCameraComp = new SplineCamera(this);
    
    // Create a spline
    Spline path;
    path.mControlPoints.emplace_back(Vector3::Zero);
    for (int i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            path.mControlPoints.emplace_back(Vector3(300.0f*(i+1), 300.0f, 300.0f));
        }
        else
        {
            path.mControlPoints.emplace_back(Vector3(300.0f * (i + 1), 0.0f, 0.0f));
        }
    }
                                             
    mCameraComp->SetSpline(path);
    mCameraComp->SetPaused(false);
}

void SplineActor::ActorInput(const uint8_t* keys)
{
    
}

void SplineActor::RestartSpline()
{
    mCameraComp->Restart();
}
