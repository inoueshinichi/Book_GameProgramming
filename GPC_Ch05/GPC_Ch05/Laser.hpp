//
//  Laser.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef Laser_hpp
#define Laser_hpp

#include "Actor.hpp"

class Laser : public Actor
{
public:
    Laser(class Game* game);
    
    void UpdateActor(float deltaTime) override;
    
private:
    class CircleComponent* mCircle;
    float mDeathTimer;
};

#endif /* Laser_hpp */
