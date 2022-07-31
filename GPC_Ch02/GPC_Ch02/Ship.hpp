//
//  Ship.hpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/15.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"

class Ship : public Actor
{
public:
    Ship(Game* game);
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }
private:
    float mRightSpeed;
    float mDownSpeed;
};

#endif /* Ship_hpp */
