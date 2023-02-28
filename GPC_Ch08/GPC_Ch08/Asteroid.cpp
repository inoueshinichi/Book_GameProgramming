//
//  Asteroid.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "Asteroid.hpp"
#include "Random.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"
#include "Game.hpp"

Asteroid::Asteroid(class Game* game)
    : Actor(game)
    , mCircle(nullptr)
{
    // 初期位置
    Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f),
                                        Vector2(512.0f, 384.0f));
    
    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture(ASSETS_DIR "Assets/Asteroid.png"));
    
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(40.0f);
    
    game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
    GetGame()->RemoveAsteroid(this);
}
