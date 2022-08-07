//
//  Component.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
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
//    virtual void ProcessInput(const uint8_t* keyState) {}
    virtual void ProcessInput(const struct InputState& state) {}
    
    int GetUpdateOrder() const { return mUpdateOrder; }
    
    virtual void OnUpdateWorldTransform() {}
    
protected:
    class Actor* mOwner;
    int mUpdateOrder;
};

#endif /* Component_hpp */
