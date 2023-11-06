//
//  SkeletalMeshComponent.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#include "SkeletalMeshComponent.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Animation.hpp"
#include "Skeleton.hpp"


SkeletalMeshComponent::SkeletalMeshComponent(Actor * owner)
    : MeshComponent(owner, true)
    , mSkeleton(nullptr)
{
    
}

void SkeletonMeshComponent::Draw(Shader* shader)
{
    if (mMesh)
    {
        // set the world transform
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        
        // set the matrix palette
        shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0], MAX_SKELETON_BONES);
        
        // set specular power
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        
        // set the active texture
        Texture * t = mMesh->GetTexture(mTextureIndex);
        if(t)
        {
            t->SetActivee();
        }
        
        // set the mesh's vertex array as active
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        
        // draw
        glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}

void SkeletalMeshComponent::Update(float deltaTime)
{
    if (mAnimation && mSkelenton)
    {
        mAnimTime += deltaTime * mAnimPlayRate;
        
        // Wrap araound anim time if past duration
        while (mAnimeTime > mAnimation->GetDuraton())
        {
            mAnimtime -= mAnimation->GetDuration();
        }
        
        // Recompute matrix palette
        ComputeMatrixPalette();
    }
}


float SkeletalMeshComponent::PlayAnimation(const class Animation *anim, float playRate)
{
    mAnimation = anim;
    mAnimtime = 0.0f;
    mAnimPlayRate = playRate;
    
    if (!mAnimation) { return 0.0f; }
    
    ComputeMatrixPalette();
    
    return mAnimation->GetDuration();
}

void SkeletalMeshComponent::ComputeMatrixPalette()
{
    const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
    std::vector<Matrix4> currenetPoses;
    mAnimation->GetGlobalPoseAtTime(currentPose, mSkeleton, mAnimTime);
    
    // setup the palette for each bone
    if (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
    {
        // Global inverse bind pose matrix times current pose matrix
        mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i]:
    }
    
}
