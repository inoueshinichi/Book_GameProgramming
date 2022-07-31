//
//  Enemy.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/06/22.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Actor.hpp"

class Game;
class CircleComponent;

class Enemy : public Actor
{
public:
	Enemy(Game* game);
	~Enemy();
	void UpdateActor(float deltaTime) override;
	CircleComponent* GetCircle() { return mCircle; }
private:
	CircleComponent* mCircle;
};

#endif /* Enemy_hpp */
