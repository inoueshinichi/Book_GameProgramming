//
//  AIPatrol.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/21.
//

#ifndef AIPatrol_hpp
#define AIPatrol_hpp

#include "AIState.hpp"

class AIComponent;

class AIPatrol : public AIState
{
public:
    AIPatrol(AIComponent* owner);
    
    // 振る舞いをオーバーライドする
    void Update(float deltaTime) override;
    void OnEnter() override {}
    void OnExit() override {}
    
    const char* GetName() const override { return "Patrol"; }
};

#endif /* AIPatrol_hpp */
