//
//  Actor.cpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"
#include <algorithm>

Actor::Actor(Game* game)
    : mState(EActive)
    , mPosition(Vector3::Zero)
    , mRotation(Quaternion::Identity)
    , mScale(1.0f)
    , mGame(game)
    , mRecomputeWorldTransform(true)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        ComputeWorldTransform();
        
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
        
        ComputeWorldTransform();
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

void Actor::ProcessInput(const uint8_t *keyState)
{
    if (mState == EActive)
    {
        for (auto comp : mComponents)
        {
            comp->ProcessInput(keyState);
        }
        
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const uint8_t *keyState)
{
    // nothing
}

void Actor::RotateToNewForward(const Vector3 &forward)
{
    // Figure out difference between original (unit x) and new
    float dot = Vector3::Dot(/*ワールド座標のX軸方向を使用する*/Vector3::UnitX, forward);
    float angle = Math::Acos(dot);
    
    // Facing down X (ほぼ正面)
    if (dot > 0.9999f)
    {
        SetRotation(Quaternion::Identity);
    }
    // Facing down -X (ほぼ反対)
    else if (dot < -0.9999f)
    {
        SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
    }
    else // その他
    {
        // Rotate about axis from cross product
        Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
        axis.Normalize();
        SetRotation(Quaternion(axis, angle));
    }
}

void Actor::ComputeWorldTransform()
{
    if (mRecomputeWorldTransform)
    {
        mRecomputeWorldTransform = false;
        
        /* 行列は行優先表現なので右方向に掛けていく. */
        // Scale, then, rotate, then, translate
        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(mPosition);
        
        // Inform components world transform updated
        for (auto comp : mComponents)
        {
            comp->OnUpdateWorldTransform(); // Actorに所属する各Componentに通知
        }
    }
}

void Actor::AddComponent(class Component *component)
{
    // Orderは昇順. 自分より更新値の高い最初のiterを探す
    // 更新値が低い程先にUpdateが入る
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    
    // Inserts element before position of iterator
    mComponents.insert(iter, component);
}

void Actor::RemoveCompoent(class Component *component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}





