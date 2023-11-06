//
//  UIScreen.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#ifndef UIScreen_hpp
#define UIScreen_hpp

#include "Math.hpp"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>

class Button
{
public:
    Button(const std::string& name,
           class Font* font,
           std::function<void()> onClick, // delegate
           const Vector2& pos,
           const Vector2& dims);
    ~Button();
    
    void SetName(const std::string& name);
    
    // getter /setter
    class Texture* GetNameTex() { return mNameTex; }
    const Vector2& GetPosition() const { return mPosition; }
    void SetHighlighted(bool sel) { mHighlighted = sel; }
    bool GetHightlited() const { return mHightlited; }
    
    // returns true if the point is within the button7s bounds
    bool ContainsPoint(const Vector2& pt) const;
    
    // delegate
    void OnClick();
    
private:
    std::function<void()> mOnClick; // delegate
    std::string mName;
    class Texture* mNameTex;
    class Font* mFont;
    Vector2 mPosition;
    Vector2 mDimentions;
    bool mHighlighted;
};

class UIScreen
{
public:
    UIScreen(class Game* game);
    virtual ~UIScreen();
    
    virtual void Update(float deltaTime);
    virtual void Draw(class Shader* shader);
    virtual void ProcessInput(const uint8_t* keys);
    virtual void HandleKeyPress(int key);
    
    // Tracks if the UI is active or closing
    enum UIState
    {
        EActive,
        EClosing,
    };
    
    // Set state to closing
    void Close();
    
    // Get state of UI screen
    UIState GetState() const { return mState; }
    // change the title text
    void SetTitle(const std::string& text,
                  const Vector3& color = Color::White,
                  int pointSize = 40);
    
    // Add a button to this screen
    void AddButton(const std::string& name, std::function<void()> onClick);
    
protected:
    // Helper to draw a texture
    void DrawTexture(class Shader* shader, class Texture* texture,
                     const Vector2& offset = Vector2::Zero,
                     float scale = 1.f);
    
    // sets the mouse mode to relative or not
    void SetRelativeMouseMode(bool relative);
    
    
    class Game* mGame;
    class Font* mFont;
    class Texture* mTitle;
    class Texture* mBackground;
    class Texture* mButtonOn;
    class Texture* mButtonOff;
    
    // Configure positions
    Vector2 mTitlePos;
    Vector2 mNextButtonPos;
    Vector2 mBGPos;
    
    // State
    UIState mState;
    
    // Lit of buttons
    std::vector<Button*> mButtons;
};

#endif /* UIScreen_hpp */
