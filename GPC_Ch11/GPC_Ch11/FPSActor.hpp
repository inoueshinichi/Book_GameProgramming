//
//  FPSActor.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#ifndef FPSActor_hpp
#define FPSActor_hpp

#include "Actor.hpp"
#include "SoundEvent.hpp"

class FPSActor final : public Actor
{
public:
    FPSActor(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keys) override;
    
    void Shoot();
    
    void SetFootstepSurface(float value);
    
    void SetVisible(bool visible);
    
    void FixCollisions();
    
private:
    class MoveComponent* mMoveComp;
    class AudioComponent* mAudioComp;
    class MeshComponent* mMeshComp;
    class FPSCamera* mCameraComp;
    class BoxComponent* mBoxComp;
    class Actor* mFPSModel;
    SoundEvent mFootstep;
    float mLastFootstep;
};

#endif /* FPSActor_hpp */
