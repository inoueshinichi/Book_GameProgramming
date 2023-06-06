//
//  BallMove.hpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/05/30.
//

#ifndef BallMove_hpp
#define BallMove_hpp

#include "MoveComponent.hpp"

class BallMove : public MoveComponent
{
public:
    BallMove(class Actor* owner);
    
    void SetPlayer(Actor* player) { mPlayer = player; }
    void Update(float deltaTime) override;
protected:
    class Actor* mPlayer;
};

#endif /* BallMove_hpp */
