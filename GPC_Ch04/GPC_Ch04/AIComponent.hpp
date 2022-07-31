//
//  AIComponent.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/21.
//

#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "Component.hpp"

#include <string>
#include <unordered_map>

class Actor;
class AIState;

class AIComponent : public Component
{
public:
    AIComponent(Actor* owner);
    
    void Update(float deltaTime) override;
    void ChangeState(const std::string& name);
    
    // 新たな状態を連想配列に登録する
    void RegisterState(AIState* state);
    
private:
    // 状態の名前とAIStateのインスタンスを対応付ける
    std::unordered_map<std::string, AIState*> mStateMap;
    // 現在の状態
    AIState* mCurrentState;
};

#endif /* AIComponent_hpp */
