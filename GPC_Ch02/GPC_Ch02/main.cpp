//
//  main.cpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/13.
//

#include <iostream>

#include "Game.hpp"

int main(int argc, const char * argv[])
{
    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
}
