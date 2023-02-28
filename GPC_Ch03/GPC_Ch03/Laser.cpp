//
//  Laser.cpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#include "Laser.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "CircleComponent.hpp"
#include "Asteroid.hpp"


Laser::Laser(Game* game)
    : Actor(game)
    , mDeathTimer(1.0f)
{
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture(ASSETS_DIR "Assets/Laser.png"));
    
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(800.0f);
    
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(11.0f);
}


void Laser::UpdateActor(float deltaTime)
{
    // 一定時間経過したらLaserは消滅する
    mDeathTimer -= deltaTime;
    if (mDeathTimer <= 0.0f)
    {
        SetState(EDead);
    }
    else
    {
        // 小惑星と衝突したのか？チェック
        for (auto ast : GetGame()->GetAsteroids())
        {
            if (Intersect(*mCircle, *(ast->GetCircle())))
            {
                SetState(EDead);
                ast->SetState(EDead);
                break; // 少なくとも１つの小惑星に当たるとLaserと小惑星は消滅する
            }
        }
    }
}

