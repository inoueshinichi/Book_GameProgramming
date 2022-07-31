//
//  Asteroid.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/19.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Actor.hpp"

class Game;
class CircleComponent;

class Asteroid : public Actor
{
public:
    Asteroid(Game* game);
    ~Asteroid();
    
    CircleComponent* GetCircle() { return mCircle; }
    
private:
    CircleComponent* mCircle;
};

#endif /* Asteroid_hpp */
