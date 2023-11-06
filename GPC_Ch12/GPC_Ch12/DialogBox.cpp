//
//  DialogBox.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/04.
//

#include "DialogBox.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include <SDL.h>

DialogBox::DialogBox(Game* game,
                     const std::string& text,
                     std::function<void()> onOK)
    : UIScreen(game)
{
    // adjust pos for dialog box
    mBGPos = Vector2(0.f, 0.f);
    mTitlePos = Vector2(0.f, 100.f);
    mNextButtonPos = Vector2(0.f, 0.f);
    
    mBackground = mGame->GetRenderer()->GetTexture(ASSETS_DIR "Assets/DialogBG.png");
    SetTitle(text, Vector3::Zero, 30);
    
    AddButton("OKButton", [onOK]() {
        onOK();
    });
    
    AddButton("CancelButton", [this]() {
        Close();
    });
}

DialogBox::~DialogBox()
{}
