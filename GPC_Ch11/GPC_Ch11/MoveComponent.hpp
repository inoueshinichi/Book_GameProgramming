//
//  MoveComponent.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/13.
//

#ifndef MoveComponent_hpp
#define MoveComponent_hpp

#include "Component.hpp"

class MoveComponent : public Component
{
public:
    MoveComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    float GetStrafeSpeed() const { return mStrafeSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
    
protected:
    float mAngularSpeed;
    float mForwardSpeed;
    float mStrafeSpeed;
};

#endif /* MoveComponent_hpp */
