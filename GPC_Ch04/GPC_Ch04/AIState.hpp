//
//  AIState.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/21.
//

#ifndef AIState_hpp
#define AIState_hpp

class AIComponent;

class AIState
{
public:
    AIState(AIComponent* owner) : mOwner(owner) {}
    virtual ~AIState() {}
    
    // 状態ごとの振る舞い
    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    
    // 状態名の取得
    virtual const char* GetName() const = 0;
    
protected:
    AIComponent* mOwner;
};

#endif /* AIState_hpp */
