//
//  SpriteComponent.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Texture.hpp"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder)
    : Component(owner)
    , mTexture(nullptr)
    , mDrawOrder(drawOrder)
    , mTexHeight(0)
    , mTexWidth(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

//void SpriteComponent::Draw(SDL_Renderer* renderer)
//{
//    if (mTexture)
//    {
//        SDL_Rect r;
//
//        // アクターのスケールに調整する
//        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
//        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
//
//        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
//        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);
//
//
//        SDL_RenderCopyEx(renderer,
//                         mTexture,
//                         &r,
//                         -Math::ToDegrees(mOwner->GetRotation()),
//                         nullptr,
//                         SDL_FLIP_NONE);
//    }
//}

void SpriteComponent::Draw(Shader* shader)
{
//    mTexWidth = mTexHeight = 64;
    // テクスチャの幅と高さで矩形をスケーリング
    Matrix4 scaleMat = Matrix4::CreateScale(
                        static_cast<float>(mTexWidth),
                        static_cast<float>(mTexHeight),
                                            1.0f);
    Matrix4 world = scaleMat * mOwner->GetWorldTransform();
    
    // ワールド変換の設定
    shader->SetMatrixUniform("uWorldTransform", world);
    
    // 現在のアクティブなテクスチャを設定
    mTexture->SetActive();
    
    // 矩形を描画
    glDrawElements(GL_TRIANGLES,    // 描画するポリゴン / プリミティブの種類
                   6,               // インデックスバッファにあるインデックスの数
                   GL_UNSIGNED_INT, // インデックスの型
                   nullptr          // 通常はnullptr
                   );
}

//void SpriteComponent::SetTexture(SDL_Texture* texture)
//{
//    mTexture = texture;
//
//    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
//}

void SpriteComponent::SetTexture(Texture* texture)
{
    mTexture = texture;
    
    // Set width/height
    mTexWidth = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}
