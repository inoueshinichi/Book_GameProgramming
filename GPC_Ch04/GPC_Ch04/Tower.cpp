#include "Tower.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

Tower::Tower(Game* game)
	: Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 200);
	sc->SetTexture(game->GetTexture(ASSET_DIR "Assets/Tower.png"));
	
	mMove = new MoveComponent(this);
	//mMove->SetAngularSpeed(Math::Pi);
	
	mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	mNextAttack -= deltaTime;
	if (mNextAttack <= 0.0f)
	{
		Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
		if (e != nullptr)
		{
			// Vector from me to enemy
			Vector2 dir = e->GetPosition() - GetPosition();
			float dist = dir.Length();
			if (dist < AttackRange)
			{
				// Rotate to face enemy
				SetRotation(Math::Atan2(-dir.y, dir.x));
				// Spawn bullet at tower position facing enemy
				Bullet* b = new Bullet(GetGame());
				b->SetPosition(GetPosition());
				b->SetRotation(GetRotation());
			}
		}
		mNextAttack += AttackTime;
	}
}
