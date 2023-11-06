//
//  BallMove.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#ifndef BallMove_hpp
#define BallMove_hpp

#include "MoveComponent.hpp"

class BallMove : public Movecomponent
{
public:
    BallMove(class Actor* owner);
    
    void SetPlay(Actor* player) { mPlayer = player; }
    void Update(float deltaTime) override;
    
protected:
    class Actor* mPlayer;
};

#endif /* BallMove_hpp */
