//
//  Game.cpp
//  GPC_Ch01
//
//  Created by Inoue Shinichi on 2022/03/07.
//

#include "Game.hpp"

#include <cmath>


const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mIsRunning(true)
    , mTickCount(0)
    , mPaddleDir(0)
{}


bool Game::Initialize()
{
    // SDL2の初期化
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("SDL2を初期化できません : %s", SDL_GetError());
        return false;
    }
    
    // ウィンドウの生成
    mWindow = SDL_CreateWindow(
                               "Game Programming in C++ (第一章)",
                               100, // ウィンドウ左上隅のx座標
                               100, // ウィンドウ左上隅のy座標
                               1024,// ウィンドウの幅(width)
                               768, // ウィンドウの高さ(height)
                               0 // フラグ(設定しないときは0)
                               );

    if (!mWindow)
    {
        SDL_Log("ウィンドウの作成に失敗しました : %s", SDL_GetError());
        return false;
    }
    
    // レンダラーの生成
    mRenderer = SDL_CreateRenderer(
                    mWindow, // 作成するレンダラーの描画対象となるウィンドウ
                    -1,      // 通常は-1
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                    );
    
    if (!mRenderer)
    {
        SDL_Log("レンダラーの作成に失敗しました : %s", SDL_GetError());
        return false;
    }
    
    
    // ボール位置
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;
    
    // ボール速度 (初期速度は右下)
    mBallVel.x = 200.0f;
    mBallVel.y = 235.0f;
    
    // パドル位置
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f / 2.0f;
    
    
    return true; // 初期化成功
}


void Game::Shutdown()
{
    // レンダラーの始末
    SDL_DestroyRenderer(mRenderer);
    
    // ウィンドウの始末
    SDL_DestroyWindow(mWindow);
    
    SDL_Log("Shutdown...");
    SDL_Quit();
}


void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::ProcessInput()
{
    SDL_Event event;
    // キューにイベントがあれば繰り返す
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
                
            default:
                break;
        }
    }
    
    // キーボードの状態を取得する
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // [ESC]キーが押されていても、ループを終える
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    
    // パドルの移動方向を取得
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W])
    { // Wキー押下で上移動
        mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S])
    { // Sキー押下で下移動
        mPaddleDir += 1;
    }
}


void Game::UpdateGame()
{
    // 前のフレームから16ms経過するまで待機
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
    
    // デルタタイムは, 前フレームとの時刻の差を秒に変換した値
    float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
    
    // 時刻を更新(次のフレームのために)
    mTickCount = SDL_GetTicks();
    
    // デルタタイムを最大値で制限する
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    
    
    /*
    // TODO : ゲームワールドのオブジェクトをデルタタイムの関数として更新する!
    */
    
    // パドルの位置を計算
    if (mPaddleDir != 0)
    {
        // 毎秒300ピクセルのスピードで動かす
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        
        // パドルが画面から出ないようにする!
        if (mPaddlePos.y < (paddleH / 2.0f + thickness))
        {
            mPaddlePos.y = paddleH / 2.0f + thickness;
        }
        else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
        {
            mPaddlePos.y = (768.0f - paddleH / 2.0f - thickness);
        }
    }
    
    // ボール位置を計算
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;
    
    // 上壁とボールの衝突判定
    if ((mBallPos.y <= thickness) && mBallVel.y < 0.0f)
    {
        mBallVel.y *= -1;
    }
    
    // 下壁とボールの衝突判定
    if ((mBallPos.y >= (768.0f - thickness)) && mBallVel.y > 0.0f)
    {
        mBallVel.y *= -1;
    }
    
    // 右壁とボールの衝突判定
    if ((mBallPos.x >= 1024.0f - thickness) && mBallVel.x > 0.0f)
    {
        mBallVel.x *= -1;
    }
    
    // パドルとボールの衝突判定
    float diff = std::abs(mPaddlePos.y - mBallPos.y);
    if (
        // もしyの差が十分に小さく
        diff <= paddleH / 2.0f &&
        // ボールが正しいx位置にあり
        mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
        // ボールが左向きに動いていれば
        mBallVel.x < 0.0f)
    {
        mBallVel.x *= -1;
    }
    
    // ボールが画面外に出たらゲーム終了
    if (mBallPos.x <= 0.0f)
    {
        mIsRunning = false;
    }
}


void Game::GenerateOutput()
{
    
    /*
     基本的な描画手順
     1) バックバッファ(ゲームのカレントバッファ)を単色でクリアする
     2) ゲームのシーン全体を描画する
     3) フロントバッファとバックバッファを交換する
     */
    
    // 1) - 1
    SDL_SetRenderDrawColor(mRenderer,
                           0,   // R
                           0,   // G
                           255, // B
                           255  // A
                           );

    // 1) - 2
    SDL_RenderClear(mRenderer);
    
    
    // ------------------------------
    // 2)

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    
    SDL_Rect wall {
        0,
        0,
        1024,
        thickness
        
    }; // x, y, w, h
    
    // 上壁
    SDL_RenderFillRect(mRenderer, &wall);
    // 下壁
    wall.y = 768 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    // 右壁
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(mRenderer, &wall);
    
    // ボール
    SDL_Rect ball {
        static_cast<int>(mBallPos.x - thickness / 2),
        static_cast<int>(mBallPos.y - thickness / 2),
        thickness,
        thickness
    };
    
    SDL_RenderFillRect(mRenderer, &ball);
    
    // パドル
    SDL_Rect paddle {
        static_cast<int>(mPaddlePos.x),
        static_cast<int>(mPaddlePos.y - paddleH / 2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    
    // ------------------------------
    
    // 3)
    SDL_RenderPresent(mRenderer);
    
    
}


