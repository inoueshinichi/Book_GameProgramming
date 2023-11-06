//
//  MeshComponent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#include "MeshComponent.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

MeshComponent::MeshComponent(Actor* owner, bool isSkeletal)
    : Component(owner)
    , mMesh(nullptr)
    , mTextureIndex(0)
    , mVisible(true)
    , mIsSkeletal(isSkeletal)
{
    mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
    mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{
    if (mMesh)
    {
        // set the world transform
        shader->SetMatrixUniform("uWorldTransform",
                                 mOwner->GetWorldTransform());
        
        // Set specular power
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        
        // Set the active texture
        Texture* t  = mMesh->GetTexture(mTextureIndex);
        if (t)
        {
            t->SetActive();
        }
        
        // set the mesh7s vertex array as active
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        
        // Draw
        glDrawElements(GL_TRIANGLES, va->GetNumIndices(),
                       GL_UNSIGNED_INT, nullptr);
    }
}
