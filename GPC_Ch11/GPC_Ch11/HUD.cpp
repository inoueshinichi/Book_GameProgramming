//
//  HUD.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/29.
//

#include "HUD.hpp"
#include "Shader.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "PhysWorld.hpp"
#include "FPSActor.hpp"
#include <algorithm>
#include "TargetComponent.hpp"
#include "Texture.hpp"

HUD::HUD(Game* game)
    : UIScreen(game)
    , mRadarRange(2000.0f)
    , mRadarRadius(92.0f)
    , mTargetEnemy(false)
{
    Renderer* r = mGame->GetRenderer();
    mHealthBar = r->GetTexture(ASSETS_DIR "Assets/HealthBar.png");
    mRadar = r->GetTexture(ASSETS_DIR "Assets/Radar.png");
    mCrosshair = r->GetTexture(ASSETS_DIR "Assets/CrosshairGreen.png");
    mCrosshairEnemy = r->GetTexture(ASSETS_DIR "Assets/CrosshairRed.png");
    mBlipTex = r->GetTexture(ASSETS_DIR "Assets/Blip.png");
    mRadarArrow = r->GetTexture(ASSETS_DIR "Assets/RadarArrow.png");
}

HUD::~HUD()
{
    
}


void HUD::Update(float deltaTime)
{
    UIScreen::Update(deltaTime);
    
    UpdateCrosshair(deltaTime);
    UpdateRadar(deltaTime);
}

void HUD::Draw(class Shader *shader)
{
    // Crosshair
    Texture* cross = mTargetEnemy ? mCrosshairEnemy : mCrosshair;
    DrawTexture(shader, cross, Vector2::Zero, 2.0f);
    
    // Radar
    const Vector2 cRadarPos(-390.0f, 275.0f);
    DrawTexture(shader, mRadar, cRadarPos, 1.0f);
    
    // Blips
    for (Vector2& blip : mBlips)
    {
        DrawTexture(shader, mBlipTex, cRadarPos + blip, 1.0f);
    }
    // Radar arrow
    DrawTexture(shader, mRadarArrow, cRadarPos);
    
    // Health bar
    DrawTexture(shader, mHealthBar, Vector2(-350.0f, -350.0f));
}

void HUD::AddTargetComponent(class TargetComponent *tc)
{
    mTargetComps.emplace_back(tc);
}

void HUD::RemoveTargetComponent(class TargetComponent *tc)
{
    auto iter = std::find(mTargetComps.begin(), mTargetComps.end(), tc);
    mTargetComps.erase(iter);
}

void HUD::UpdateCrosshair(float deltaTime)
{
    // Reset to regular cursor
    mTargetEnemy = false;
    
    // Make a line segment
    const float cAimDist = 5000.0f;
    Vector3 start, dir;
    
    mGame->GetRenderer()->GetScreenDirection(start, dir);
    
    LineSegment ls(start, start + dir * cAimDist);
    
    // Segment cast
    PhysWorld::CollisionInfo info;
    if (mGame->GetPhysWorld()->SegmentCast(ls, info))
    {
        // Is this a target?
        for (auto tc: mTargetComps)
        {
            if (tc->GetOwner() == info.mActor)
            {
                mTargetEnemy = true;
                break;
            }
        }
    }
}


void HUD::UpdateRadar(float deltaTime)
{
    // 一つ前のフレームの輝点位置をクリア
    mBlips.clear();
    
    // プレイヤーの位置をレーダー座標に変換(xが前方,zが上方)
    Vector3 playerPos = mGame->GetPlayer()->GetPosition();
    Vector2 playerPos2D(playerPos.y, playerPos.x);
    // 同様にプレイヤーの前方ベクトルを変換
    Vector3 playerForward = mGame->GetPlayer()->GetForward();
    Vector2 playerForward2D(playerForward.x, playerForward.y);
    
    // atan2を使ってレーダーの回転を求める
    float angle = Math::Atan2(playerForward2D.y, playerForward2D.x);
    // 2次元の回転行列を得る
    Matrix3 rotMat = Matrix3::CreateRotation(angle);
    
    // 輝点の位置を取得する
    for (auto tc : mTargetComps)
    {
        Vector3 targetPos = tc->GetOwner()->GetPosition();
        Vector2 actorPos2D(targetPos.y, targetPos.x);
        
        // プレイヤーからターゲットへのベクトルを計算
        Vector2 playerToTarget = actorPos2D - playerPos2D;
        
        // 範囲内にあるか?
        if (playerToTarget.LengthSq() <= (mRadarRange * mRadarRange))
        {
            // playerToTargetを画面上のレーダーの
            // 中心からのオフセットに変換する
            Vector2 blipPos = playerToTarget;
            blipPos *= mRadarRadius/mRadarRange;
            
            // blipPosを回転する
            blipPos = Vector2::Transform(blipPos, rotMat);
            mBlips.emplace_back(blipPos);
        }
    }
}
