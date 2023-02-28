//
//  MeshComponent.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#include "MeshComponent.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

MeshComponent::MeshComponent(Actor* owner)
    : Component(owner)
    , mMesh(nullptr)
    , mTextureIndex(0)
    , mVisible(true)
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
        // Set the world transform
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        
        // Set specular power
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        
        // Set the active texture
        Texture* t = mMesh->GetTexture(mTextureIndex);
        
        if (t)
        {
            t->SetActive();
        }
        
        // Set the mesh's vertex array as active
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        
        // Draw
        glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}
