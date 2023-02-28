//
//  Asteroid.cpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/19.
//

#include "Asteroid.hpp"
#include "Random.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"
#include "Game.hpp"


Asteroid::Asteroid(Game* game)
    : Actor(game)
    , mCircle(nullptr)
{
    // 初期位置
    Vector2 randPos = Random::GetVector(Vector2::Zero
                                        , Vector2(2014.0f, 768.0f));
    SetPosition(randPos);
    
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    
    // スプライト
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture(ASSETS_DIR "Assets/Asteroid.png"));
    
    // 移動機能
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    
    // 仮想円
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(40.0f);
    
    game->AddAsteroid(this);
}


Asteroid::~Asteroid()
{
    GetGame()->RemoveAsteroid(this);
}
