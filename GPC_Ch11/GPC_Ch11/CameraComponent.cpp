//
//  CameraComponent.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/14.
//

#include "CameraComponent.hpp"
#include "Actor.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "AudioSystem.hpp"

CameraComponent::CameraComponent(Actor* owner,
                                 int updateOrder)
    : Component(owner, updateOrder)
{}

void CameraComponent::SetViewMatrix(const Matrix4 &view)
{
    // Pass view matrix to renderer and audio system
    Game* game = mOwner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
    game->GetAudioSystem()->SetListener(view);
}


