//
//  Actor.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/28.
//

#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"

#include <algorithm>

Actor::Actor(class Game* game)
    : mState(EActive)
    , mPosition(Vector2::Zero)
    , mScale(1.0f)
    , mRotation(0.0f)
    , mGame(game)
    , mRecomputeWorldTransform(true)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    
    // コンポーネントの削除
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        ComputeWorldTransform(); // 1
        
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
        
        ComputeWorldTransform(); // Update中にワールド行列が変化する場合に備えて.
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
    // nothing
}

//void Actor::ProcessInput(const uint8_t* keyState)
//{
//    if (mState == EActive)
//    {
//        for (auto comp : mComponents)
//        {
//            comp->ProcessInput(keyState);
//        }
//
//        // アクター独自
//        ActorInput(keyState);
//    }
//}

void Actor::ProcessInput(const struct InputState& state)
{
    if (mState == EActive)
    {
        for (auto comp : mComponents)
        {
            comp->ProcessInput(state);
        }
        
        // アクター独自
        ActorInput(state);
    }
}

//void Actor::ActorInput(const uint8_t* keyState)
//{
//    // nothing
//}

void Actor::ActorInput(const struct InputState& state)
{
    // nothing
}

void Actor::AddComponent(class Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    
    // イテレータの前に挿入
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(class Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

// Transform
void Actor::ComputeWorldTransform()
{
    if (mRecomputeWorldTransform)
    {
        mRecomputeWorldTransform = false;
        // まずスケーリング、次に回転、最後に平行移動
        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(
             Vector3(mPosition.x, mPosition.y, 0.0f));
        
        // ワールド行列の更新をコンポーネントに通知する
        for (auto comp : mComponents)
        {
            comp->OnUpdateWorldTransform();
        }
    }
}
