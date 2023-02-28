//
//  Game.hpp
//  GPC_Ch01
//
//  Created by Inoue Shinichi on 2022/03/07.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

#include "SDL.h"
// (x,y)
struct Vector2
{
    float x;
    float y;
};


class Game
{
public:
    Game();
    // ゲームを初期化する
    bool Initialize();
    // ゲームオーバーまでゲームループを実行する
    void RunLoop();
    // ゲームをシャットダウンする
    void Shutdown();
private:
    // ゲームループのためのヘルパー関数
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    // SDL2が作るウィンドウ
    SDL_Window* mWindow;
    
    // ゲームの続行を指示する
    bool mIsRunning;
    
    // SDL2のレンダラー
    SDL_Renderer* mRenderer;
    
    // パドルの位置
    Vector2 mPaddlePos;
    
    // パドルの移動方向 (0: 不動, +1: 下移動, -1: 上移動)
    int mPaddleDir;
    
    // ボールの位置
    Vector2 mBallPos;
    
    // ボールの速度
    Vector2 mBallVel;
    
    // デルタタイム
    Uint32 mTickCount;
};

#endif /* Game_hpp */
