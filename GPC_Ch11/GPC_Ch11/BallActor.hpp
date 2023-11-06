//
//  BallActor.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#ifndef BallActor_hpp
#define BallActor_hpp

#include "Actor.hpp"

class BallActor final : public Actor
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
