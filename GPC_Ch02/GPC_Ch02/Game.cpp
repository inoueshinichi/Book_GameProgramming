//
//  Game.cpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/13.
//

#include "SDL2/SDL_image.h"

#include <algorithm>

#include "Game.hpp"
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "Ship.hpp"
#include "BGSpriteComponent.hpp"


Game::Game()
: mWindow(nullptr)
, mRenderer(nullptr)
, mIsRunning(true)
, mUpdatingActors(false)
, mShip(nullptr)
{}

bool Game::Initialize()
{
    // 初期化
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL2: %s", SDL_GetError());
        return false;
    }
    
    // ウィンドウ生成
    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)"
                               , 100
                               , 100
                               , 1024
                               , 768
                               , 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    // レンダラー生成
    mRenderer = SDL_CreateRenderer(mWindow
                                   , -1
                                   , SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_PRESENTVSYNC
                                   );
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
        
    // PNG画像(スプライト)の初期化
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    
    // データ読み込み
    LoadData();
    
    // TicksCountの初期化
    mTicksCount = SDL_GetTicks();
    
    return true;
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
    // キューにイベントがあれば繰り返す
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
                
            default:
                break;
        }
    }
    
    // キーボードの状態を取得する
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    
    // キーボードの状態を取得する
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    
    // 船への入力
    mShip->ProcessKeyboard(state);
}


void Game::UpdateGame()
{
    /* デルタタイムを計算 */
    
    // 前のフレームから16ms(=30fps)経過するまで待機
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    // デルタタイムは, 前フレームとの時刻の差を秒に変換した値
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    // 時刻を更新(次のフレームのために)
    mTicksCount = SDL_GetTicks();
    
    // デルタタイムを最大値で制限する
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    
    /* すべてのActorを更新 */
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    
    // 待ちになっていたActorをmActorsに移動
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    
    // 死んだActorを一時配列に追加
    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    
    // 死んだActorを消す(mActorsから削除される)
    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
    
    // すべてのスプライト(コンポーネント)を描画
    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }
    
    SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::AddActor(Actor *actor)
{
    // Actorの更新中なら待ちに追加
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    // mPendingActorsの残りをチェック
    auto iter = std::find(mPendingActors.begin(),
                          mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // 削除したいactorとmPendingActorsの最後の要素を交換する
        // ※ eraseによる配列の内部コピーを防ぐため
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    
    // mActorsの残りをチェック
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // 削除したいactorとmPendingActorsの最後の要素を交換する
        // ※ eraseによる配列の内部コピーを防ぐため
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::LoadData()
{
    // プレイヤー船を作成
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(100.0f, 384.0f));
    mShip->SetScale(1.5f);
    
    // 背景アクターを作成
    Actor* temp = new Actor(this);
    temp->SetPosition(Vector2(512.0f, 384.0f));
    // フォールバック背景(最奥背景)を作成
    BGSpriteComponent* bg; std::vector<SDL_Texture*> bgtexs;
    /*BGSpriteComponent* */bg = new BGSpriteComponent(temp, 10);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    /*std::vector<SDL_Texture*> */bgtexs = {
        GetTexture(ASSETS_DIR "Assets/Farback01.png"),
        GetTexture(ASSETS_DIR "Assets/Farback02.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-100.0f);
    
    // 星々背景(中間背景)を作成
    bg = new BGSpriteComponent(temp, 50);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    bgtexs = {
        GetTexture(ASSETS_DIR "Assets/Stars.png"),
        GetTexture(ASSETS_DIR "Assets/Stars.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-200.0f);
    
    /**
            前景(船) - 中間背景(星々) - 最奥背景(フォールバック)
     */
}

void Game::UnloadData()
{
    // アクターを削除
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    
    // テクスチャを削除
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
    SDL_Texture* tex = nullptr;
    
    // 既にTextureは連想配列に格納されているかチェック
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        // ファイルから読み込み
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file: %s", fileName.c_str());
            return nullptr;
        }
        
        // SurfaceからTextureを作成
        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if (!tex)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }
        
        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::AddSprite(SpriteComponent* sprite)
{
    // ソート済みの配列で挿入点を見つける
    // (それは自分よりも順序の高い最初の要素位置になる)
    int myDrawOrder = sprite->GetDrawOrder();
    
    /* myDrawOrder = 55
     draw-array: 50, 60, 70, 100, ...
     insert: ..., 50, <55>, 60, ...
     */
    auto iter = mSprites.begin();
    for ( ;
         iter != mSprites.end();
         ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    
    // イテレータの位置の前に要素を挿入する
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}
