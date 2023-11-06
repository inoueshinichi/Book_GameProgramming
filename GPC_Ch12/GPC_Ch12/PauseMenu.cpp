//
//  PauseMenu.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/04.
//

#include "PauseMenu.hpp"
#include "Game.hpp"
#include "DialogBox.hpp"
#include <SDL.h>

PauseMenu::PauseMenu(Game* game)
    : UIScreen(game)
{
    mGame->SetState(Game::EPaused);
    SetRelativeMouseMode(false);
    SetTitle("PauseTitle");
    
    AddButton("ResumeButton",
              [this]() {
        Close();
    });
    
    AddButton("QuitButton",
              [this]() {
        new DialogBox(mGame,
                      "QuitText",
                      [this]() {
            mGame->SetState(Game::EQuit);
        });
    });
}

PauseMenu::~PauseMenu()
{
    SetRelativeMouseMode(true);
    mGame->SetState(Game::EGameplay);
}

void PauseMenu::HandleKeyPress(int key)
{
    UIScreen::HandleKeyPress(key);
    
    if (key == SDLK_ESCAPE)
    {
        Close();
    }
}
