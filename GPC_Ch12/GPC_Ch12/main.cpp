//
//  main.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/09/28.
//

#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game game;
    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }
    
    game.Shutdown();
    return 0;
}
