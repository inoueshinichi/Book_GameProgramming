//
//  MoveComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
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
    void SetForwardSpeed(float speed) { mAngularSpeed = speed; }
    void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
protected:
    float mAngularSpeed;
    float mForwardSpeed;
    float StrafeSpeed;
};

#endif /* MoveComponent_hpp */
