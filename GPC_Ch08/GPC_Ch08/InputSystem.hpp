//
//  InputSystem.hpp
//  GPC_Ch08
//
//  Created by Inoue Shinichi on 2022/08/01.
//

#ifndef InputSystem_hpp
#define InputSystem_hpp

#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.hpp"

// ボタン状態
enum ButtonState
{
    ENone,
    EPressed,
    EReleased,
    EHeld
};

// キーボード入力の補助クラス
class KeyboardState
{
public:
    friend class InputSystem;
    bool GetKeyValue(SDL_Scancode keyCode) const;
    ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
    const Uint8* mCurrState;
    Uint8 mPrevState[SDL_NUM_SCANCODES];
};

// マウス入力の補助クラス
class MouseState
{
public:
    friend class InputSystem;
    
    // pos
    const Vector2& GetPosition() const { return mMousePos; }
    const Vector2& GetScrollWheel() const { return mScrollWheel; }
    bool IsRelative() const { return mIsRelative; }
    
    // button
    bool GetButtonValue(int button) const;
    ButtonState GetButtonState(int button) const;
private:
    Vector2 mMousePos;
    Vector2 mScrollWheel;
    Uint32 mCurrButtons;
    Uint32 mPrevButtons;
    bool mIsRelative;
};

// コントローラ入力の補助クラス
class ControllerState
{
public:
    friend class InputSystem;
    
    // ボタン
    bool GetButtonValue(SDL_GameControllerButton button) const;
    ButtonState GetButtonState(SDL_GameControllerButton button) const;
    
    bool GetIsConnected() const { return mIsConnected; }
    
    // トリガー
    float GetLeftTrigger() const { return mLeftTrigger; }
    float GetRightTrigger() const { return mRightTrigger; }
    
    // スティック
    const Vector2& GetLeftStick() const { return mLeftStick; }
    const Vector2& GetRightStick() const { return mRightStick; }
    
private:
    Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
    Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];
    bool mIsConnected;
    float mLeftTrigger;
    float mRightTrigger;
    Vector2 mLeftStick;
    Vector2 mRightStick;
};

// ラッパークラス
struct InputState
{
    KeyboardState Keyboard;
    MouseState Mouse;
    ControllerState Controller;
};

class InputSystem
{
public:
    bool Initialize();
    void Shutdown();
    
    void PrepareForUpdate();
    void Update();
    void ProcessEvent(union SDL_Event& event);
    
    const InputState& GetState() const { return mState; }
    
    void SetRelativeMouseMode(bool value);
private:
    float Filter1D(int input);
    Vector2 Filter2D(int inputX, int inputY);
    
    InputState mState;
    SDL_GameController* mController;
};

#endif /* InputSystem_hpp */
