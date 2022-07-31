//
//  Actor.hpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/13.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.hpp"

// 前方宣言
class Game;
class Component;

class Actor
{
public:
    // Actorの状態管理用
    enum State
    {
        EActive,
        EPaused,
        EDead
    };
    
    Actor(Game* game);
    virtual ~Actor();
    
public:
    // Gameから呼び出される更新関数(オーバーライド不可)
    void Update(float deltaTime);
    // Actorが持つ全コンポーネントを更新(オーバーライド不可)
    void UpdateComponents(float deltaTime);
    // Actor独自の更新処理(オーバーライド可能)
    virtual void UpdateActor(float deltaTime);
    
    // Getter/Setter
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }
    
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }
    
    Game* GetGame() { return mGame; }
    
    
    // コンポーネントの追加/削除
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

private:
    // Actorの状態
    State mState;
    // 座標変換
    Vector2 mPosition; // Actorの中心位置
    float mScale;      // Actorのスケール(1.0fが100%)
    float mRotation;   // 回転角度(rad)
    // Actorが持つコンポーネント
    std::vector<Component*> mComponents;
    Game* mGame;
    
};

#endif /* Actor_hpp */
