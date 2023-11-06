//
//  SkeletalMeshComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#ifndef SkeletalMeshComponent_hpp
#define SkeletalMeshComponent_hpp

#include "MeshComponent.hpp"
#include "MatrixPalette.hpp"

class SkeletalMeshComponent: public MeshComponent
{
public:
    SkeletalMeshComponent(class Actor* owner);
    
    // Draw this mesh component
    void Draw(class Shader* shader) override;
    
    void Update(float deltaTime) override;
    
    // setter
    void SetSkeleton(const class Skeleton* sk) { mSkeleton = sk; }
    
    // play an animation, returns the length of the animation
    float PlayAnimation(const class Animation* anim, float playRate = 1.0f);
    
protected:
    void ComputeMatrixPalette();
    
    MatrixPalette mPalette;
    const class Skeleton* mSkeleton;
    const class Aniamtion* mAnimation;
    float mAnimPlayRate;
    float mAnimTime;
};

#endif /* SkeletalMeshComponent_hpp */
