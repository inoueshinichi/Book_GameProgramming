//
//  PauseMenu.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/29.
//

#include "PauseMenu.hpp"
#include "SDL.h"
#include "Game.hpp"
#include "DialogBox.hpp"

PauseMenu::PauseMenu(Game* game)
    : UIScreen(game)
{
    mGame->SetState(Game::EPaused);
    SetRelativeMouseMode(false);
    SetTitle("PauseTitle");
    
    AddButton("ResumeButton", [this]() {
        Close();
    });
    
    AddButton("QuitButton", [this]() {
        new DialogBox(mGame, "QuitText",
                      [this]() {
            mGame->SetState(Game::EQuit);
        });
    });
}

PauseMenu::~PauseMenu()
{
    mGame->SetState(Game::EGamePlay);
}

void PauseMenu::HandleKeyPress(int key)
{
    UIScreen::HandleKeyPress(key);
    
    if (key == SDLK_ESCAPE)
    {
        Close();
    }
}



