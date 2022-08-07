//
//  main.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/28.
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
