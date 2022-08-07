//
//  Actor.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/28.
//

#ifndef Actor_hpp
#define Actor_hpp

#include "Math.hpp"

#include <vector>
#include <cstdint>

class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };
    
    Actor(class Game* game);
    virtual ~Actor();
    
    // アクター派生クラス用インターフェース
    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    
    virtual void UpdateActor(float deltaTime);
    
    /* Gameから呼び出される関数(オーバーライド不可) */
//    void ProcessInput(const uint8_t* keyState);
    void ProcessInput(const struct InputState& state);
    
    /* アクター固有の入力関数(オーバーライド可能) */
//    virtual void ActorInput(const uint8_t* keyState);
    virtual void ActorInput(const struct InputState& state);
    
    
    // 位置、方向、スケール, 状態
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos)
    {
        mPosition = pos;
        mRecomputeWorldTransform = true;
    }
    float GetScale() const { return mScale; }
    void SetScale(float scale)
    {
        mScale = scale;
        mRecomputeWorldTransform = true;
    }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation)
    {
        mRotation = rotation;
        mRecomputeWorldTransform = true;
    }
    
    // Transform
    void ComputeWorldTransform();
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }
    
    Vector2 GetForward() const
    {
        return Vector2(Math::Cos(mRotation), Math::Sin(mRotation));
    }
    
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }
    
    
    class Game* GetGame() { return mGame; }
    
    
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    
private:
    State mState;
    
    // Transform
    Vector2 mPosition;
    float mScale;
    float mRotation;
    Matrix4 mWorldTransform;
    bool mRecomputeWorldTransform;
    
    std::vector<class Component*> mComponents;
    
    class Game* mGame;
};

#endif /* Actor_hpp */
