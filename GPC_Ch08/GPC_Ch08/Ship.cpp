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

#include "InputSystem.hpp"

Ship::Ship(class Game* game)
    : Actor(game)
    , mSpeed(400.0f)
    , mLaserCooldown(0.0f)
{
    SpriteComponent* sc = new SpriteComponent(this, 150);
    sc->SetTexture(game->GetTexture(ASSET_DIR "Assets/Ship.png"));
    
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
    // クールタイムを減らす
    mLaserCooldown -= deltaTime;
    
    // 位置を更新(by velocity)
    Vector2 pos = GetPosition();
    pos += mVerocityDir * mSpeed * deltaTime;
    SetPosition(pos);
    
    // 姿勢(回転)の更新
    float angle = Math::Atan2(mRotationDir.y, mRotationDir.x);
    SetRotation(angle);
}

void Ship::ActorInput(const InputState& state)
{
    if (state.Controller.GetRightTrigger() > 0.25f &&
        mLaserCooldown <= 0.0f)
    {
        // レーザー生成
        Laser* laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        
        // クールダウンタイムをリセット
        mLaserCooldown = 0.5f;
    }
    
    if (state.Controller.GetIsConnected())
    {
        mVerocityDir = state.Controller.GetLeftStick();
        if (!Math::NearZero(state.Controller.GetRightStick().Length()))
        {
            mRotationDir = state.Controller.GetRightStick();
        }
    }
}

