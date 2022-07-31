//
//  Laser.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#ifndef Laser_hpp
#define Laser_hpp

#include "Actor.hpp"

class Game;
class CircleComponent;

class Laser : public Actor
{
public:
    Laser(Game* game);
    
    void UpdateActor(float deltaTime) override;
    
private:
    CircleComponent* mCircle;
    float mDeathTimer;
};

#endif /* Laser_hpp */
