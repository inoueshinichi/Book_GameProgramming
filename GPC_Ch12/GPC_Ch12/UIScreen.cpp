//
//  UIScreen.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#include "UIScreen.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "Font.hpp"

UIScreen::UIScreen(Game* game)
    : mGame(game)
    , mTitle(nullptr)
    , mBackground(nullptr)
    , mTitlePos(0.f, 300.f)
    , mNextButtonPos(0.f, 200.f)
    , mBGPos(0.f, 250.f)
    , mState(EActive)
{
    // Add to UI Stack
    mGame->PushUI(this);
    mFont = mGame->GetFont(ASSETS_DIR "Assets/Carlito-Regular.ttf");
    mButtonOn = mGame->GetRenderer()->GetTexture(ASSETS_DIR "Assets/ButtonYellow.png");
    mButtonOff = mGame->GetRenderer()->GetTexture(ASSETS_DIR "Assets/ButtonBlue.png");
}

UIScreen::~UIScreen()
{
    if (mTitle)
    {
        mTitle->Unload();
        delete mTitle;
    }
    
    for (auto b : mButtons)
    {
        delete b;
    }
    
    mButtons.clear();
}



void UIScreen::Update(float deltaTime)
{}

void UIScreen::Draw(Shader* shader)
{
    // Draw background (if exists)
    if (mBackground)
    {
        DrawTexture(shader, mBackground, mBGPos);
    }
    
    // Draw title (if exists)
    if (mTitle)
    {
        DrawTexture(shader, mTitle, mTitlePos);
    }
    
    // draw buttons
    for (auto b : mButtons)
    {
        // draw background of button
        Texture* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
        DrawTexture(shader, tex, b->GetPosition());
        
        // Draw text of button
        DrawTexture(shader, b->GetNameTex(), b->GetPosition());
    }
    
    // override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const uint8_t *keys)
{
    // do we have buttons?
    if (!mButtons.empty())
    {
        // get position of mouse
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        // Convert to (0,0) center to coordinates
        Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
        // y up x right
        mousePos.x -= mGame->GetRenderer()->GetScreenWidth() * 0.5f;
        mousePos.y = mGame->GetRenderer()->GetScreenHeight() * 0.5f - mousePos.y;
        
        // Highlight any buttons
        for (auto b : mButtons)
        {
            if (b->ContainsPoint(mousePos))
            {
                b->SetHighlighted(true);
            }
            else
            {
                b->SetHightlited(false);
            }
        }
    }
}


void UIScreen::HandleKeyPress(int key)
{
    switch (key)
    {
        case SDL_BUTTON_LIGHT:
            if (!mButtons.empty())
            {
                for (auto b : mButtons)
                {
                    if (b->GetHighlited())
                    {
                        b->OnClick();
                        break;
                    }
                }
            }
            break;
            
        default:
            break;
    }
}

void UIScreen::Close()
{
    mState = EClosing;
}

void UIScreen::SetTitle(const std::string& text,
                        const Vector3& color, int pointSize)
{
    // Clear out previous title texture if it exists
    if (mTitle)
    {
        mTitle->Unload();
        delete mTitle;
        mTitle = nullptr;
    }
    
    mTitle = mFont->RenderText(tex, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
    // ボタン寸法
    Vector2 dims(static_cast<float>(mButtonOn->GetWidth()),
                 static_cast<float>(mButtonOn->GetHeight()));
    Button* b = new Button(name, mFont, onClick, mNextButtonPos, dims);
    mButtons.emplace_back(b);
    
    // Update position of next button
    // Move down by height of button plus padding
    mNextButtonPos.y -= mButtonOff->GetHeight() + 20.0f;
}

void UIScreen::DrawTexture(class Shader *shader,
                           class Texture *texture,
                           const Vector2& offset,
                           float scale)
{
    // Scale the quad by the width / height of texture
    Matrix4 scaleMat = Matrix4::CreateScale(
                            static_cast<float>(texture->GetWidth()) * scale,
                            static_cast<float>(texture->GetHeight()) * scale);
                                            
    // Translate to position on screen
    Matrix4 transMat = Matrix4::CreateTranslation(Vector3(offset.x, offset.y, 0.f));
                                            
    // set world transform
    Matrix4 world = scaleMat * transMat; // 2D専用
    shader->SetMatrixUniform("uWorldTransform", world);
    texture->SetActive();
    
    // Draw quad by OpenGL
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIScreen::SetRelativeMouseMode(bool relative)
{
    if (relative)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        // Make an intial call to get relative to clear out.
        SDL_GetRelativeMouseState(nullptr, nullptr);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}


// Button
Button::Button(const std::string& name,
               Font* font,
               std::function<void()> onClick,
               const Vector2& pos,
               const Vector2& dims)
    : mOnClick(onClick)
    , mNameTex(nullptr)
    , mFont(font)
    , mPosition(pos)
    , mDimensions(dims)
    , mHighlighted(false)
{
    SetName(name);
}

Button::~Button()
{
    if (mNameTex)
    {
        mNameTex->Unload();
        delete mNameTex;
    }
}

void Button::SetName(const std::string& name)
{
    mName = name;
    if (mNameTex)
    {
        mNameTex->Unload();
        delete mNameTex;
        mNameTex = nullptr;
    }
    
    mNameTex = mFont->RenderText(mName);
}

bool Button::containsPoint(const Vector2& pt) const
{
    bool no = pt.x < (mPosition.x - mDimentions.x / 2.f) ||
              pt.x > (mPosition.x + mDimentions.x / 2.f) ||
              pt.y < (mPosition.y - mDimentions.y / 2.f) ||
              pt.y > (mPosition.y + mDimentions.y / 2.f);
    
    return !no;
}

void Button::OnClick()
{
    if (mOnClick)
    {
        mOnClick();
    }
}



















                         
