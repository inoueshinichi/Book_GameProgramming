//
//  AIComponent.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/21.
//

#include "AIComponent.hpp"
#include "AIState.hpp"

#include <SDL.h>

AIComponent::AIComponent(Actor* owner)
    : Component(owner)
    , mCurrentState(nullptr)
{}


void AIComponent::RegisterState(AIState* state)
{
    mStateMap.emplace(state->GetName(), state);
}


void AIComponent::Update(float deltaTime)
{
    if (mCurrentState)
    {
        mCurrentState->Update(deltaTime);
    }
}


void AIComponent::ChangeState(const std::string& name)
{
    // まず現在の状態を抜ける
    if (mCurrentState)
    {
        mCurrentState->OnExit();
    }
    
    // 新しい状態を連想配列から探す
    auto iter = mStateMap.find(name);
    if (iter != mStateMap.end())
    {
        mCurrentState = iter->second;
        // 新しい状態に入る
        mCurrentState->OnEnter();
    }
    else
    {
        SDL_Log("AIState %s の状態はありません", name.c_str());
        mCurrentState = nullptr;
    }
}
