#include "Enemy.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "NavComponent.hpp"
#include "Grid.hpp"
#include "Tile.hpp"
#include "CircleComponent.hpp"
#include <algorithm>

Enemy::Enemy(Game* game)
	: Actor(game)
{
	// 敵配列に追加
	game->GetEnemies().emplace_back(this);
	
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture(ASSETS_DIR "Assets/Airplane.png"));
	// Set position at start tile
	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	// Setup a nav component at the start tile
	NavComponent* nc = new NavComponent(this);
	nc->SetForwardSpeed(150.0f);
	nc->StartPath(GetGame()->GetGrid()->GetStartTile()); // 移動開始
	// Setup a circle for collision
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
	// Remove from enemy vector
	auto iter = std::find(GetGame()->GetEnemies().begin(),
	                               GetGame()->GetEnemies().end(),
	                               this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	// Am I near the end tile ?
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		SetState(EDead);
	}
}
