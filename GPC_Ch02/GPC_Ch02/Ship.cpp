//
//  Ship.cpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/15.
//

#include "Ship.hpp"
#include "AnimSpriteComponent.hpp"
#include "Game.hpp"

Ship::Ship(Game* game)
    : Actor(game)
    , mRightSpeed(0.0f)
    , mDownSpeed(0.0f)
{
    // アニメーション・スプライトコンポーネントを作成
    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> anims = {
        game->GetTexture(ASSETS_DIR "Assets/Ship01.png"),
        game->GetTexture(ASSETS_DIR "Assets/Ship02.png"),
        game->GetTexture(ASSETS_DIR "Assets/Ship03.png"),
        game->GetTexture(ASSETS_DIR "Assets/Ship04.png"),
    };
    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    // 速度とデルタタイムに基づいて位置を更新
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;
    // 位置の制限
    if (pos.x < 25.0f)
    {
        pos.x = 25.0f;
    }
    else if (pos.x > 500.0f)
    {
        pos.x = 500.0f;
    }
    
    if (pos.y < 25.0f)
    {
        pos.y = 25.0f;
    }
    else if (pos.y > 743.0f)
    {
        pos.y = 743.0f;
    }
    
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    // right/left
    if (state[SDL_SCANCODE_D])
    {
        mRightSpeed += 250.0f;
    }
    if (state[SDL_SCANCODE_A])
    {
        mRightSpeed -= 250.0f;
    }
    // up/down
    if (state[SDL_SCANCODE_S])
    {
        mDownSpeed += 300.0f;
    }
    if (state[SDL_SCANCODE_W])
    {
        mDownSpeed -= 300.0f;
    }
}
