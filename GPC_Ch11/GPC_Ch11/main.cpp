//
//  main.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/06/06.
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
