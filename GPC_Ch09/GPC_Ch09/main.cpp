//
//  main.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/08.
//

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
    return 0;
}
