//
//  Game.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
//

#include "Game.hpp"
#include "SDL2/SDL_image.h"
#include <algorithm>
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "Grid.hpp"
#include "Enemy.hpp"
#include "AIComponent.hpp"
#include "AIState.hpp"

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
    
    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 4)"
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
    
    mRenderer = SDL_CreateRenderer(mWindow
                                   , -1
                                   , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    LoadData();

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
    
    // タワーディフェンスゲームにおいて、塔を建てるコマンド
    if (keyState[SDL_SCANCODE_B])
    {
        mGrid->BuildTower();
    }
    
    // マウスイベント
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
    {
        mGrid->ProcessClick(x, y);
    }
    
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->ProcessInput(keyState);
    }
    mUpdatingActors = false;
}


void Game::UpdateGame()
{
    // 60FPSのデルタタイムを確保
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
    
    // アクターの更新
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    
    // 待機アクターをアクティブ化
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    
    // デッドアクターの処理
    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    
    for (auto actor : deadActors)
    {
        delete actor; // 疑問：ヌルポになったmActors配列の要素の後処理はどうしているのか？？？
                      // 回答：deleteによるデストラクタ発動により、内部でmGame->RemoveActor関数が発動して、mActors配列と mPendingActors配列から該当アクターのポインタを消去している.
    }
}


void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 34, 139, 34, 255);
    SDL_RenderClear(mRenderer);
    
    // スプライトの描画
    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }
    
    // 画面更新
    SDL_RenderPresent(mRenderer);
}


void Game::LoadData()
{
    mGrid = new Grid(this);
    
    // For testing AIComponent
    //Actor* a = new Actor(this);
    //AIComponent* aic = new AIComponent(a);
    //// Register states with AIComponent
    //aic->RegisterState(new AIPatrol(aic));
    //aic->RegisterState(new AIDeath(aic));
    //aic->RegisterState(new AIAttack(aic));
    //// Start in patrol state
    //aic->ChangeState("Patrol");
}


void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back(); // mGame->RemoveActorが発動.
    }
    
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}


SDL_Texture* Game::GetTexture(const std::string& fileName)
{
    SDL_Texture* tex = nullptr;
    // Is the texture already in the map?
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        // Load from file
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        // Create texture from surface
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
    // If we're updating actors, need to add to pending
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
    // Is it in pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    // Is it in actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}


void Game::AddSprite(SpriteComponent* sprite)
{
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int myDrawOrder = sprite->GetDrawOrder();
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

    // Inserts element before position of iterator
    mSprites.insert(iter, sprite);
}


void Game::RemoveSprite(SpriteComponent* sprite)
{
    // (We can't swap because it ruins ordering)
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}


Enemy* Game::GetNearestEnemy(const Vector2& pos)
{
    Enemy* best = nullptr;
    
    if (mEnemies.size() > 0)
    {
        best = mEnemies[0];
        
        float bestDistSq = (pos - mEnemies[0]->GetPosition()).LengthSq();
        for (size_t i = 1; i < mEnemies.size(); i++)
        {
            float newDistSq = (pos - mEnemies[i]->GetPosition()).LengthSq();
            if (newDistSq < bestDistSq)
            {
                bestDistSq = newDistSq;
                best = mEnemies[i];
            }
        }
    }
    
    return best;
}
