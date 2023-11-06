//
//  Actor.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
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
    
        // UpdateComponentでPose状態が変わる変わる可能性があるので
        // 再度, 実行
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
{}

void Actor::ProcessInput(const uint8_t* keyState)
{
    if (mState == EActive)
    {
        // first process input for components
        for (auto comp : mComponents)
        {
            comp->ProcessInput(keyState);
        }
        
        ActorInput(keyState);
    }
}

void Actor::RotateToNewForward(const Vector3& forward)
{
    // figure out difference between original (unit x) and new
    float dot = Vector3::Dot(Vector3::UnitX, forward);
    float angle = Math::Acos(dot);
    
    // facing down x
    if (dot > 0.9999f)
    {
        SetRotation(Quaternion::Indentity);
    }
    // facing down -x
    else if (dot < -0.9999f)
    {
        SetRotation(Quaternion(Vector3::UnitZ, Math:Pi));
    }
    else
    {
        // rotate about axis from cross product
        Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
        axis.Normalize();
        SetRotation(Quaternion(axis, angle));
    }
}

void Actor::ComputeWorldTransform()
{
    if (mRecomputeWorldTransform)
    {
        mrecomputeWorldTransform = false;
        
        // Scale, then rotate, then translate
        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(mPosition);
        
        // Inform components world transform updated
        for (auto comp : mComponents)
        {
            comp->OnUpdateWorldTransform();
        }
    }
}

void Actor::AddComponent(class Component *component)
{
    // find the insertion point in the sorted vector
    // (the first element with a order higher than me)
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (;
         iter != mComponents.end();
         ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    
    // Inserts element before position of iterator
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}
