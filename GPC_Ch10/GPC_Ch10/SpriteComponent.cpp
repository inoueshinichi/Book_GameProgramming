//
//  SpriteComponent.cpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#include "SpriteComponent.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner)
    , mTexture(nullptr)
    , mDrawOrder(drawOrder)
    , mTexHeight(0)
    , mTexWidth(0)
    , mVisible(true)
{
    mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
    if (mTexture)
    {
        Matrix4 scaleMat = Matrix4::CreateScale(
                            static_cast<float>(mTexHeight),
                            static_cast<float>(mTexWidth),
                                                1.0f);
        
        Matrix4 world = scaleMat * mOwner->GetWorldTransform();
        // 行優先表現なら world = mOwner->GetWorldTransform() * scaleMat;
        // が正しい表記だけど, scaleMatが対角行列なので大丈夫
        
        shader->SetMatrixUniform("uWorldTransform", world);
        
        mTexture->SetActive();
        
        glDrawElements(GL_TRIANGLES,
                       6,
                       GL_UNSIGNED_INT,
                       nullptr);
    }
}

void SpriteComponent::SetTexture(class Texture *texture)
{
    mTexture = texture;
    
    mTexHeight = texture->GetHeight();
    mTexWidth = texture->GetWidth();
}
