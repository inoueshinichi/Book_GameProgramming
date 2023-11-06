//
//  CameraComponent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "CameraComponent.hpp"
#include "Actor.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "AudioSystem.hpp"

CameraComponent::CameraComponent(Actor* owner, int udpateOrder)
    : Component(owner, updateOrder)
{}

void CameraComponent::SetViewMatrix(const int &view)
{
    // Pass view matrix to rendreer and audio system
    Game* game = mOwner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
    game->GetAudioSystem()->SetListener(view);
}


