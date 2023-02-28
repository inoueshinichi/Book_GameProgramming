//
//  CameraComponent.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/02/28.
//

#include "CameraComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "AudioSystem.hpp"

CameraComponent::CameraComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder)
{}

void CameraComponent::SetViewMatrix(const Matrix4 &view)
{
    // ビュー行列をレンダラーとオーディオシステムにわたす
    Game* game = mOwner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
    game->GetAudioSystem()->SetListener(view);
}
