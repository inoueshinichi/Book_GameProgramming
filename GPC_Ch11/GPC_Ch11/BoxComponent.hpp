//
//  BoxComponent.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#ifndef BoxComponent_hpp
#define BoxComponent_hpp

#include "Component.hpp"
#include "Collision.hpp"

class BoxComponent : public Component
{
public:
    BoxComponent(class Actor* owner, int updateOrder = 100);
    ~BoxComponent();
    
    void OnUpdateWorldTransform() override;
    
    void SetObjectBox(const AABB& model) { mObjectBox = model; }
    const AABB& GetWorldBox() const { return mWorldBox; }
    
    void SetShouldRotate(bool value) { mShouldRotate = value; }
    
private:
    AABB mObjectBox;
    AABB mWorldBox;
    bool mShouldRotate;
};

#endif /* BoxComponent_hpp */
