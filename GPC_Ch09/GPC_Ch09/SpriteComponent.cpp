//
//  SpriteComponent.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#include "SpriteComponent.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

#include "SDL2/SDL.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    :Component(owner)
    ,mTexture(nullptr)
    ,mDrawOrder(drawOrder)
    ,mTexWidth(0)
    ,mTexHeight(0)
    ,mVisible(true)
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
        // Scale the quad by the width/height of texture
        Matrix4 scaleMat = Matrix4::CreateScale(
            static_cast<float>(mTexWidth),
            static_cast<float>(mTexHeight),
            1.0f);
        
        Matrix4 world = scaleMat * mOwner->GetWorldTransform();
        
        // Since all sprites use the same shader/vertices,
        // the game first sets them active before any sprite draws
        
        // Set world transform
        shader->SetMatrixUniform("uWorldTransform", world);
        // Set current texture
        mTexture->SetActive();

        // Draw quad
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // from Shader.hpp
    }
}

void SpriteComponent::SetTexture(Texture* texture)
{
    mTexture = texture;
    // Set width/height
    mTexWidth = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}
