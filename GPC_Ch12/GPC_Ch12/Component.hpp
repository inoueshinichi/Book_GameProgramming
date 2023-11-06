//
//  Component.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef Component_hpp
#define Component_hpp

#include <cstdint>

class Component
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const uint8_t* keyState) {}
    virtual void OnUpdateWorldTransform() {}
    
    class Actor* GetOwner() { return mOwner; }
    int GetUpdateOrder() const { return mUpdateOrder; }
    
protected:
    class Actor* mOwner;
    int mUpdateOrder;
}

#endif /* Component_hpp */
