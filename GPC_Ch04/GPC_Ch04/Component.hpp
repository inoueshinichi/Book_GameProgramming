//
//  Component.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
//

#ifndef Component_hpp
#define Component_hpp

#include <cstdint>

class Actor;

class Component
{
public:
    Component(Actor* owner, int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const uint8_t* keyState) {}
    int GetUpdateOrder() const { return mUpdateOrder; }
protected:
    Actor* mOwner;
    int mUpdateOrder;
};

#endif /* Component_hpp */
