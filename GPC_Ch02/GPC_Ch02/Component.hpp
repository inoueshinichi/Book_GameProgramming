//
//  Component.hpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/13.
//

#ifndef Component_hpp
#define Component_hpp

// 前方宣言
class Actor;

class Component
{
public:
    // コンストラクタ
    // updateOrderが小さいコンポーネントほど早く更新される
    Component(Actor* owner, int updateOrder = 100);
    
    // デストラクタ
    virtual ~Component();
    
    // このコンポーネントをdeltaTimeで更新する
    virtual void Update(float deltaTime);
    
    int GetUpdateOrder() const { return mUpdateOrder; }
    
protected:
    // 所有Actor
    Actor* mOwner;
    // コンポーネントの更新順序
    int mUpdateOrder;
};




#endif /* Component_hpp */
