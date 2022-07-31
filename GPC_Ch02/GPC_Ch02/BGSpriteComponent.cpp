//
//  BGSpriteComponent.cpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/15.
//

#include "BGSpriteComponent.hpp"
#include "Actor.hpp"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mScrollSpeed(0.0f)
{}


void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture *> &textures)
{
    int count = 0;
    for (auto tex : textures)
    {
        BGTexture temp;
        temp.mTexture = tex;
        // それぞれのテクスチャは画面幅分のオフセットを持つ
        temp.mOffset.x = count * mScreenSize.x;
        temp.mOffset.y = 0;
        mBGTextures.emplace_back(temp);
        count++;
    }
}


void BGSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);
    
    for (auto& bg : mBGTextures)
    {
        // xのオフセットを更新
        bg.mOffset.x += mScrollSpeed * deltaTime;
        
        // もし画面から完全に出たらオフセットを
        // 最後の背景テクスチャの右にリセットする
        if (bg.mOffset.x < -mScreenSize.x)
        {
            bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer)
{
    // 背景の描画(※ビューポートからはみ出た領域は描画されない)
    for (auto& bg : mBGTextures)
    {
        SDL_Rect r;
        
        r.w = static_cast<int>(mScreenSize.x);
        r.h = static_cast<int>(mScreenSize.y);
        
        // Actor中心から矩形の左上座標を計算
        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);
        
        SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
        
    }
}
