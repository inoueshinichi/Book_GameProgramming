//
//  OrbitActor.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/01/25.
//

#include "OrbitActor.hpp"
#include "MeshComponent.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "OrbitCamera.hpp"
#include "MoveComponent.hpp"

OrbitActor::OrbitActor(Game* game)
    : Actor(game)
{
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(
        game->GetRenderer()->GetMesh(                                                    ASSETS_DIR "Assets/RacingCar.gpmesh"));
    SetPosition(Vector3(0.0f, 0.0f, -100.0f));
    
    mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const uint8_t *keyState)
{
    // Mouse rotation
    // Get relative movement from SDL
    int x, y;
    Uint32 buttons = SDL_GetRelativeMouseState(&x, &y);
    
    // Only apply rotation if right-click is held
    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        // Assume mouse movement is usually between -500 and +500
        const int maxMouseSpeed = 600;
        // Rotation/sec at maximum speed
        const float maxOrbitSpeed = Math::Pi * 8;
        float yawSpeed = 0.0f;
        if (x != 0)
        {
            // Convert to およそ[-1.0,1.0]
            yawSpeed = static_cast<float>(x) / maxMouseSpeed;
            yawSpeed *= maxOrbitSpeed;
        }
        mCameraComp->SetYawSpeed(-yawSpeed);
        
        // Compute pitch
        float pitchSpeed = 0.0f;
        if (y != 0)
        {
            // Convert to およそ[-1.0,1.0]
            pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
            pitchSpeed *= maxOrbitSpeed;
        }
        mCameraComp->SetPitchSpeed(pitchSpeed);
    }
}

void OrbitActor::SetVisible(bool visible)
{
    mMeshComp->SetVisible(visible);
}
