//
//  FPSActor.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef FPSActor_hpp
#define FPSActor_hpp

#include "Actor.hpp"
#include "SoundEvent.hpp"

class FPSActor : public Actor
{
public:
    FPSActor(class Game* game);
    ~FPSActor();
    void ActorInput(const uint8_t *keyState) override;
    void UpdateActor(float deltaTime) override;
    
    void SetFootstepSurface(float value);
    void SetVisible(bool visible);
    
private:
    class MoveComponent* mMoveComp;
    class AudioComponent* mAudioComp;
    class MeshComponent* mMeshComp;
    class FPSCamera* mCameraComp;
    class Actor* mFPSModel;
    SoundEvent mFootstep;
    float mLastFootstep;
};

#endif /* FPSActor_hpp */
