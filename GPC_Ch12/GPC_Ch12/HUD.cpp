//
//  HUD.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#include "HUD.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "PhysWorld.hpp"
#include "FollowActor.hpp"
#include <algorithm>
#include "TargetComponent.hpp"

HUD::HUD(Game* game)
    : UIScreen(game)
    , mRadarRange(2000.0f)
    , mRadarRadius(92.0f)
    , mTargetEnemy(false)
{
    Renderer* r = mGame->GetRenderer();
    mHealthBar = r->GetTexture(ASSETS_DIR "Assets/HealthBar.png");
    mRadar = r->GetTexture(ASSETS_DIR "Asseets/Radar.png");
    mCrosshair = r->GetTexture(ASSETS_DIR "Assets/Crosshair.png");
    mCrosshairEnemy = r->GetTexture(ASSETS_DIR "Assets/CrosshairRed.png");
    mBlipTex = r->GetTexture(ASSETS_DIR "Assets/Blip.png");
    mRadarArrow = r->GetTexture(ASSETS_DIR "Assets/RadarArrow.png");
}

HUD::HUD()
{
    
}

void HUD::Update(float deltaTime)
{
    UIScreen::Update(deltaTime);
    
    UpdateCrosshair(deltaTime);
    UpdateRader(deltaTime);
}

void HUD::Draw(Shader* shader)
{
    // Crosshair
    // Texture* cross = mTargetEnemy ? mCrosshairEnemy : mCrosshair;
    // DrawTexture(shader, cross, Vector2::Zero, 2.0f);
    
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
    
    // Healthbar
    // DrawTexture(shader, mHealthbar, Vector2(-350.0f, -350.0f);
}

void HUD::AddTargetComponent(TargetComponent* tc)
{
    mTargetComps.emplace_back(tc);
}

void HUD::RemoveTargetComponent(TargetComponent* tc)
{
    auto iter = std::find(mTargetComps.begin(), mTargetComps.end(), tc);
    mTargetComps.erase(iter);
}

void HUD::UpdateCrosshair(float deltaTime)
{
    // reset to regular cursor
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
        // Is this a a target?
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

void HUD::UpdateRader(float deltaTime)
{
    // Clear blip position from last frame
    mBlips.clear();
    
    // convert player position to radar coordinates (x forward, z up)
    Vector3 playerPos = mGame->GetPlayer()->GetPosition();
    Vector2 playerPos2D(/*forward*/playerPos.y, /*right*/playerPos.x);
    
    // Ditto for player forward
    Vector3 playerForward = mGame->GetPlayer()->GetForward();
    Vector2 playerForward2D(/*forward*/playerForward.x, /*right*/playerForward.y);
    
    // Use atan2 to get rotation of radar
    float angle = Math::Atan2(/*x*/playerForward2D.y, /*y*/playerForward2D.x);
    
    // Make a 2D rotation matrix
    Matrix3 rotMat = Matrix3::CreateRotation(angle);
    
    // Get positions of blips
    for (auto tc : mTargetComps)
    {
        Vector3 targetPos = tc->GetOwner()->GetPosition();
        Vector2 actorPos2D(/*x*/targetPos.y, /*y*/targetPos.y);
        
        // Calculate vector between player and target
        Vector2 playerToTarget = actorPos2D - playerPos2D;
        
        // Radarのレンジ内にあるか
        if (palyerToTarget.LengthSq() <= (mRadarRange * mRadarRange))
        {
            // convert playerToTarget into an offset from
            // the center of the on-screen radar
            Vector2 blipPos = playerToTarget;
            blipPos *= mRadarRange / mRadarRange;
            
            // Rotate blipPos
            blipPos = Vector2::Transform(blipPos, rotMat);
            mBlips.emplace_back(blipPos);
        }
    }
}


