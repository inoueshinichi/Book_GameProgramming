//
//  FollowActor.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef FollowActor_hpp
#define FollowActor_hpp

#include "Actor.hpp"

class FollowActor : public Actor
{
public:
    FollowActor(class Game* game);
    
    void ActorInput(const uint8_t* keys) override;
    
    void SetVisible(bool visible);
    
private:
    class MoveComponent* mMoveComp;
    class FollowCamera* mCameraComp;
    
    class SkeltalMeshComponent* mMeshComp;
    bool mMoving;
};

#endif /* FollowActor_hpp */
