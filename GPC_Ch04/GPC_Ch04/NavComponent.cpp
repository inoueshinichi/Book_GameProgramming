//
//  NavComponent.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
//

#include "NavComponent.hpp"
#include "Tile.hpp"


NavComponent::NavComponent(Actor* owner, int updateOrder)
    : MoveComponent(owner, updateOrder)
    , mNextNode(nullptr)
{}

/*経路ノード上で次の親ノードにアクターを移動させる*/
void NavComponent::Update(float deltaTime)
{
    // もし次の点に到達したら、経路の次の点に進む
    if (mNextNode)
    {
        Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition();
        if (Math::NearZero(diff.Length(), 2.0f))
        {
            mNextNode = mNextNode->GetParent();
            TurnTo(mNextNode->GetPosition());
        }
    }
    
    // アクターを前進させる
    MoveComponent::Update(deltaTime);
}

/*目標地点に自身の方向を向ける*/
void NavComponent::TurnTo(const Vector2& pos)
{
    // 自身からposへの方向ベクトル
    Vector2 dir = pos - mOwner->GetPosition();
    // 角度
    float angle = Math::Atan2(-dir.y, dir.x);
    mOwner->SetRotation(angle);
}


/*現在ノードから親ノードに方向を向ける*/
void NavComponent::StartPath(const Tile* start)
{
    mNextNode = start->GetParent();
    TurnTo(mNextNode->GetPosition());
}
