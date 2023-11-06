//
//  BallActor.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef BallActor_hpp
#define BallActor_hpp

#include "Actor.hpp"

class BallActor : public Actor
{
public:
    BallActor(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    void SetPlayer(Actor* player);
    
    void HitTarget();
    
private:
    class AudioComponent* mAudioComp;
    class BallMove* mMyMove;
    float mLifeSpan;
};

#endif /* BallActor_hpp */
