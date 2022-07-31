//
//  main.cpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/12.
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
