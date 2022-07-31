//
//  CameraActor.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/20.
//

#ifndef CameraActor_hpp
#define CameraActor_hpp

#include "Actor.hpp"

class CameraActor : public Actor
{
public:
    CameraActor(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keys) override;
private:
    class MoveComponent* mMoveComp;
};

#endif /* CameraActor_hpp */
