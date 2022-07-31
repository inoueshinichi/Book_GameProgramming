//
//  Actor.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.hpp"
#include <cstdint>

class Game;
class Component;

class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };
    
    Actor(Game* game);
    virtual ~Actor();
    
    void Update(float deltaTime);
    
    
    void ProcessInput(const uint8_t* keyState);
    virtual void ActorInput(const uint8_t* keyState);
    
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }
    
    Vector2 GetForward() const
    {
        return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation));
    }
    
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }
    
    Game* GetGame() { return mGame; }
    
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    
protected:
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);
    
private:
    State mState;
    
    Vector2 mPosition;
    float mScale;
    float mRotation;
    
    std::vector<Component*> mComponents;
    Game* mGame;
};

#endif /* Actor_hpp */
