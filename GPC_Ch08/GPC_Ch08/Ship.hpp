//
//  Ship.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"

class Ship : public Actor
{
public:
    Ship(class Game* game);
    
    void UpdateActor(float deltaTime) override;
//    void ActorInput(const uint8_t* keyState) override;
    void ActorInput(const struct InputState& state) override;
    
private:
    float mLaserCooldown;
    Vector2 mVerocityDir;
    Vector2 mRotationDir;
    float mSpeed;
    
};

#endif /* Ship_hpp */
