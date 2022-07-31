//
//  Game.cpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#include "Game.hpp"
#include "SDL2/SDL_image.h"

#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "Ship.hpp"
#include "Asteroid.hpp"
#include "Random.hpp"

#include <algorithm>

Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mIsRunning(true)
    , mUpdatingActors(false)
{}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 3)"
                               , 100
                               , 100
                               , 1024
                               , 768
                               , 0
                               );
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow
                                  , -1
                                  , SDL_RENDERER_ACCELERATED
                                  | SDL_RENDERER_PRESENTVSYNC
                                  );
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    
    Random::Init();
    
    LoadData();
    
    mTicksCount = SDL_GetTicks();
    
    return true;
}


void Game::RunLoop()
{
    while ( mIsRunning )
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    
    /* アクターに必要な入力 */
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->ProcessInput(keyState);
    }
    mUpdatingActors = false;
}


void Game::UpdateGame()
{
    // 16ms(60FPS)のデルタタイムを確保
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    
    mTicksCount = SDL_GetTicks();
    
    /* アクターの更新 */
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    
    // 待ちアクターを追加
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    
    // 期限切れアクターを一時配列に格納
    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    
    // 期限切れアクターを削除(mActorsから除去)
    // 疑問：deadActors配列でヌルポにしたらmActors配列の要素も自動的に消える?
    for (auto actor : deadActors)
    {
        delete actor;
        /*ここで、mActors配列の要素を削除しないと行けないのでは？*/
    }
}


void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer
                           , 220
                           , 220
                           , 220
                           , 255
                           );
    SDL_RenderClear(mRenderer);
    
    // スプライト・コンポーネントの描画
    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }
    
    SDL_RenderPresent(mRenderer);
    
}


void Game::LoadData()
{
    // 船
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(512.0f, 384.0f));
    mShip->SetRotation(Math::PiOver2);
    
    // 小惑星
    const int numAsteroids = 20;
    for (int i = 0; i < numAsteroids; ++i)
    {
        new Asteroid(this);
    }
}


void Game::UnloadData()
{
    // アクターの削除
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    
    // テクスチャの削除
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}


SDL_Texture* Game::GetTexture(const std::string &fileName)
{
    SDL_Texture* tex = nullptr;
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }
        
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

void Game::AddAsteroid(Asteroid* ast)
{
    mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
    auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
    if (iter != mAsteroids.end())
    {
        mAsteroids.erase(iter);
    }
}


void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}


void Game::AddActor(Actor* actor)
{
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
    auto iter = std::find(mPendingActors.begin()
                          , mPendingActors.end()
                          , actor);
    if (iter != mPendingActors.end())
    {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
        
    iter = std::find(mActors.begin()
                          , mActors.end()
                          , actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}


void Game::AddSprite(SpriteComponent *sprite)
{
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for ( ;
         iter != mSprites.end();
         ++iter)
    {
        // 配列は昇順
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    
    // iterの前に挿入
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    // スワップする必要なし
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}
