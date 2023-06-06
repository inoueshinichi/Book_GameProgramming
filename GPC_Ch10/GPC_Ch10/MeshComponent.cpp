//
//  MeshComponent.cpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
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

void MeshComponent::Draw(class Shader *shader)
{
    if (mMesh)
    {
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        
        Texture* t = mMesh->GetTexture(mTextureIndex);
        if (t)
        {
            t->SetActive();
        }
        
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        
        glDrawElements(GL_TRIANGLES,
                       va->GetNumIndices(),
                       GL_UNSIGNED_INT,
                       nullptr);
    }
}
