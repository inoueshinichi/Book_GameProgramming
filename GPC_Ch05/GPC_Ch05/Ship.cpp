//
//  Ship.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "Ship.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"
#include "Game.hpp"
#include "Laser.hpp"

Ship::Ship(class Game* game)
    : Actor(game)
    , mLaserCooldown(0.0f)
{
    SpriteComponent* sc = new SpriteComponent(this, 150);
    sc->SetTexture(game->GetTexture(ASSETS_DIR "Assets/Ship.png"));
    
    InputComponent* ic = new InputComponent(this);
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
    ic->SetMaxForwardSpeed(300.0f);
    ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
    mLaserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState)
{
    if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
    {
        // レーザーを生成
        Laser* laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        
        // クールダウンタイムをリセット
        mLaserCooldown = 0.5f;
    }
}
