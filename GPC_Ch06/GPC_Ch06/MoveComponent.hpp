//
//  MoveComponent.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/15.
//

#ifndef MoveComponent_hpp
#define MoveComponent_hpp

#include "Component.hpp"

class MoveComponent : public Component
{
public:
    // Lower update order to update first
    MoveComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
    float mAngularSpeed;
    float mForwardSpeed;
};

#endif /* MoveComponent_hpp */
