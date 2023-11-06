//
//  DialogBox.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/30.
//

#include "DialogBox.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include <SDL.h>

DialogBox::DialogBox(Game* game, const std::string& text,
                     std::function<void()> onOK)
    : UIScreen(game)
{
    // Adjust positions for dialog box
    mBGPos = Vector2(0.0f, 0.0f);
    mTitlePos = Vector2(0.0f, 100.0f);
    mNextButtonPos = Vector2(0.0f, 0.0f);
    
    mBackground = mGame->GetRenderer()->GetTexture(
                                                   ASSETS_DIR "Assets/DialogBG.png");
    
    SetTitle(text, Vector3::Zero, 30);
    
    AddButton("OKButton", [onOK]() {
        onOK();
    });
    
    AddButton("CancelButton", [this]() {
        Close();
    });
}

DialogBox::~DialogBox()
{
    
}
