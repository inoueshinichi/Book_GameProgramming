//
//  Asteroid.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Actor.hpp"

class Asteroid : public Actor
{
public:
    Asteroid(class Game* game);
    ~Asteroid();
    
    class CircleComponent* GetCircle() { return mCircle; }
    
private:
    class CircleComponent* mCircle;
};

#endif /* Asteroid_hpp */
