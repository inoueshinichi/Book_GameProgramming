//
//  Bullet.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/04/12.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "Actor.hpp"

class Game;
class CircleComponent;

class Bullet : public Actor
{
public:
	Bullet(Game* game);
	void UpdateActor(float deltaTime) override;
private:
	CircleComponent* mCircle;
	float mLiveTime;
};

#endif /* Bullet_hpp */
