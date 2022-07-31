//
//  Laser.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "Laser.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "CircleComponent.hpp"
#include "Asteroid.hpp"

Laser::Laser(class Game* game)
    : Actor(game)
    , mDeathTimer(1.0f)
{
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture(ASSET_DIR "Assets/Laser.png"));
    
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
        // 小惑星と衝突したのかチェック
        for (auto ast : GetGame()->GetAsteroids())
        {
            if (Intersect(*mCircle, *(ast->GetCircle())))
            {
                SetState(EDead);
                ast->SetState(EDead);
                break;
            }
        }
    }
}
