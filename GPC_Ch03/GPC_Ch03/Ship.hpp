//
//  Ship.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"

class Game;

class Ship : public Actor
{
public:
    Ship(Game* game);
    
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
    
private:
    float mLaserCooldown;
};

#endif /* Ship_hpp */
