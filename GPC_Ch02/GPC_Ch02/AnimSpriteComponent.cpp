//
//  AnimSpriteComponent.cpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/15.
//

#include "AnimSpriteComponent.hpp"
#include "Math.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mCurrFrame(0.0f)
    , mAnimFPS(24.0f)
{}


void AnimSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime); // 親の関数を実行
    
    if (mAnimTextures.size() > 0)
    {
        // フレームレートとデルタタイムに基づいて
        // カレントフレームを更新する
        mCurrFrame += mAnimFPS * deltaTime;
        
        // 必要に応じてカレントフレームを巻き戻す
        while (mCurrFrame >= mAnimTextures.size())
        {
            mCurrFrame -= mAnimTextures.size();
        }
        
        // 現時点のテクスチャを設定する
        SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
    }
}


void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
    mAnimTextures = textures;
    if (mAnimTextures.size() > 0)
    {
        // 初期化
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}
