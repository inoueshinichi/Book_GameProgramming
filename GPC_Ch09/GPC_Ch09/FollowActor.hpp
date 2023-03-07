//
//  FollowActor.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/01/25.
//

#ifndef FollowActor_hpp
#define FollowActor_hpp

#include "Actor.hpp"

class FollowActor : public Actor
{
public:
    FollowActor(class Game* game);
    ~FollowActor() {}
    
    void ActorInput(const uint8_t* keyState) override;
    
    void SetVisible(bool visible);
private:
    class MoveComponent* mMoveComp;
    class FollowCamera* mCameraComp;
    class MeshComponent* mMeshComp;
    
};

#endif /* FollowActor_hpp */
