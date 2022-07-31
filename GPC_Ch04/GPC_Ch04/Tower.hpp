//
//  Tower.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/06/22.
//

#ifndef Tower_hpp
#define Tower_hpp

#include "Actor.hpp"

class Game;
class MoveComponent;

class Tower : public Actor
{
public:
	Tower(Game* game);
	void UpdateActor(float deltaTime) override;
private:
	MoveComponent* mMove;
	float mNextAttack;
	const float AttackTime = 2.5f;
	const float AttackRange = 100.0f;
};

#endif /* Tower_hpp */
