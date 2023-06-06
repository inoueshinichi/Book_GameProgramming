//
//  Actor.hpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.hpp"
#include <cstdint>

class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead,
    };
    
    Actor(class Game* game);
    virtual ~Actor();
    
    /* Update */
    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);
    
    /* Input */
    void ProcessInput(const uint8_t* keyState);
    virtual void ActorInput(const uint8_t* keyState);
    
    void RotateToNewForward(const Vector3& forward);
    
    void ComputeWorldTransform();
    
    /* Position */
    const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos)
    {
        mPosition = pos;
        mRecomputeWorldTransform = true;
    }
    
    /* Scale */
    float GetScale() const { return mScale; }
    void SetScale(float scale)
    {
        mScale = scale;
        mRecomputeWorldTransform = true;
    }
    
    /* Rotation(Quaternion) */
    const Quaternion& GetRotation() const { return mRotation; }
    void SetRotation(const Quaternion& rotation)
    {
        mRotation = rotation;
        mRecomputeWorldTransform = true;
    }
    
    
    const Matrix4& GetWorldTransform() const
    {
        return mWorldTransform;
    }
    
    Vector3 GetForward() const
    {
        // 毎回World座標系のUnitXをActorのmRotationで回転させたものを計算する
        return Vector3::Transform(Vector3::UnitX, mRotation);
    }
    
    Vector3 GetRight() const
    {
        // 毎回World座標系のUnitXをActorのmRotationで回転させたものを計算する
        return Vector3::Transform(Vector3::UnitY, mRotation);
    }
    
    
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }
    
    class Game* GetGame() { return mGame; }
    
    void AddComponent(class Component* component);
    void RemoveCompoent(class Component* component);
    
private:
    State mState;
    
    Matrix4 mWorldTransform;
    Vector3 mPosition;
    Quaternion mRotation;
    float mScale;
    bool mRecomputeWorldTransform;
    
    std::vector<class Component*> mComponents;
    class Game* mGame;
};

#endif /* Actor_hpp */
