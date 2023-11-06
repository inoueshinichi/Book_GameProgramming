//
//  BoxComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#ifndef BoxComponent_hpp
#define BoxComponent_hpp

#include "Component.hpp"
#include "Collision.hpp"

class BoxComponent : public Component
{
public:
    BoxComponent(class Actor* owner, int updateOrder=100);
    ~BoxComponent();
    
    void OnUpdateWorldTransform() override;
    
    void SetObjectBox(const AABB& model) { mObjectBox = model; }
    const AABB& GetWorldBox() const { return mWorldBox; }
    
    void SetShouldRotate(bool value) { mShouldRotate = value; }
    
private:
    AABB mObjectBox; // モデル読み込み時から一切変更しない原本
    AABB mWorldBox;  // アクターのPose変化ごとに追従して変化する
    bool mShouldRotate;
}

#endif /* BoxComponent_hpp */
