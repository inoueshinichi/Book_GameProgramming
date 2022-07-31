//
//  NavComponent.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
//

#ifndef NavComponent_hpp
#define NavComponent_hpp

#include "MoveComponent.hpp"
#include "Math.hpp"

class Actor;
class Tile;

class NavComponent : public MoveComponent
{
public:
    // 最初に更新するためにアップデート値を小さく設定している
    NavComponent(Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    void StartPath(const Tile* start);
    void TurnTo(const Vector2& pos);
private:
    const Tile* mNextNode;
};

#endif /* NavComponent_hpp */
