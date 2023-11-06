//
//  BallMove.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#include "BallMove.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "PhysWorld.hpp"
#include "TargetActor.hpp"
#include "BallActor.hpp"

BallMove::BallMove(Actor * owner)
    : MoveComponent(owner)
{}

void BallMove::Update(float deltaTime)
{
    // Construct segment in direction of travel
    const float segmentLength = 30.0f;
    Vector3 start = mOwner->GetPosition();
    Vector3 dir = mOwner->GetForward();
    Vector3 end = start + dir * segmentLength;
    
    // Create line segment
    LineSegment ls(start, end);
    
    // test segment vs world
    PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
    PhysWorld::CollisionInfo rusage_info;
    
    // don't collide vs player
    if (phys->SegmentCast(ls, info) && info.mActor != mPlayer)
    {
        // if we collided, reflect hte ball about the normal
        dir = Vector3::Reflect(dir, info.mNormal);
        mOwner->RotateToNewForward(dir);
        
        // did we hit a target ?
        TargetActor* target = dynamic_cast<TargetActor*>(info.mActor);
        if (target)
        {
            static_cast<BallActor*>(mOwner)->HitTarget();
        }
    }
    
    // base class update moves based on forward speed
    MoveComponent::Update(deltaTime); // 基本的な移動処理を基底クラス側で実行
}
