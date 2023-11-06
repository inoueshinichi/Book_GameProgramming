//
//  SpriteComponent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
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

SpriteComponent::~Spritecomponent()
{
    mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
    if (mTexture)
    {
        // Scale the quad by the width / height of texture
        Matrix4 scaleMat = Matrix4::CreateScale(
                                                static_cast<float>(mTexWidth),
                                                static_cast<float>(mTexHeight),
                                                1.0f);
        
        Matrix4 world = scaleMat * mOwner->GetWorldTransform();
        
        // since all sprites use the same shader/vertices,
        // the game first set them active before any sprite draws.
        
        // Set world transform
        shader->SetMatrixUniform("uWorldTransform", world);
        // Set current texture
        mTexture->SetActive();
        // Draw quad
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void SpriteComponent::SetTexture(Texture* texture)
{
    mTexture = texture;
    
    mTexWidth = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}
