//
//  Game.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/28.
//

#include "Game.hpp"
#include "SDL2/SDL_image.h"
#include <GL/glew.h>

#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "Ship.hpp"
#include "Asteroid.hpp"
#include "Random.hpp"

#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include <algorithm>


Game::Game()
    : mWindow(nullptr)
    //, mRenderer(nullptr)
    , mSpriteShader(nullptr)
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
    
    /* OpenGLの設定 */
    // コアOpenGLプロファイルを使う
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // バージョン3.3を指定
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // RGBA各チャネル8ビットのカラーバッファを使う
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // ダブルバッファを有効にする
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // ハードウェアアクセラレーションを使う
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    
    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 5)"
                               , 100
                               , 100
                               , 1024
                               , 768
                               , SDL_WINDOW_OPENGL); // SDLウィンドウでOpenGLを利用する.
    
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    // OpenGLコンテキスト生成
    mContext = SDL_GL_CreateContext(mWindow);
    
    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }
    
    // 一部のプラットフォームで無駄なエラーが出るので消す
    glGetError();
    
    // シェーダ作成
    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }
    
    // 四角形の頂点を作成
    CreateSpriteVerts();
    
//    mRenderer = SDL_CreateRenderer(mWindow
//                                   , -1
//                                   , SDL_RENDERER_ACCELERATED
//                                   | SDL_RENDERER_PRESENTVSYNC );
    
//    if (!mRenderer)
//    {
//        SDL_Log("Failed to create renderer: %s", SDL_GetError());
//        return false;
//    }
    
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
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
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
    
    // 待機アクターを追加
    for (auto pending : mPendingActors)
    {
        // ペンディング状態のアクターでもワールド行列を計算
        pending->ComputeWorldTransform();
        
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
    for (auto actor : deadActors)
    {
        delete actor; // actorオブジェクトのデストラクタ側でmActors配列から対象ポインタを削除している
    }
}

void Game::GenerateOutput()
{
//    // SDLレンダラーの初期化
//    SDL_SetRenderDrawColor(mRenderer
//                           , 220
//                           , 220
//                           , 220
//                           , 255);
//    SDL_RenderClear(mRenderer);
    
    /* OpenGLによる描画処理 */
    glClearColor(0.86f, 0.86f, 0.86f, 1.0f); // 背景を灰色に設定
    glClear(GL_COLOR_BUFFER_BIT); // カラーバッファをクリア
    
    // TODO: シーンを描画
    
    // アルファ・ブレンディング
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, // srcFactorはsrcAlpha
                GL_ONE_MINUS_SRC_ALPHA // dstFactorは(1-srcAlpha)
                );
    
    // スプライトのシェーダと頂点配列オブジェクトをアクティブ化
    mSpriteShader->SetActive();
    mSpriteVerts->SetActive();
    
    // スプライト・コンポーネントの描画
    for (auto sprite : mSprites)
    {
        //sprite->Draw(mRenderer);
        sprite->Draw(mSpriteShader);
    }
    
//    // SDLによる描画
//    SDL_RenderPresent(mRenderer);
    
    // ダブルバッファによるバッファ交換
    SDL_GL_SwapWindow(mWindow);
}

void Game::LoadData()
{
    // 船
    mShip = new Ship(this);
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
//        SDL_DestroyTexture(i.second);
        i.second->Unload();
        delete i.second;
    }
    mTextures.clear();
}

//SDL_Texture* Game::GetTexture(const std::string &fileName)
//{
//    SDL_Texture* tex = nullptr;
//    auto iter = mTextures.find(fileName);
//    if (iter != mTextures.end())
//    {
//        tex = iter->second;
//    }
//    else
//    {
//        SDL_Surface* surf = IMG_Load(fileName.c_str());
//        if (!surf)
//        {
//            SDL_Log("Failed to load texture file %s", fileName.c_str());
//            return nullptr;
//        }
//
//        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
//        SDL_FreeSurface(surf);
//        if (!tex)
//        {
//            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
//            return nullptr;
//        }
//
//        mTextures.emplace(fileName.c_str(), tex);
//    }
//
//    return tex;
//}

Texture* Game::GetTexture(const std::string& fileName)
{
    Texture* tex = nullptr;
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        tex = new Texture();
        if (tex->Load(fileName))
        {
            mTextures.emplace(fileName, tex);
        }
        else
        {
            delete tex;
            tex = nullptr;
        }
    }

    return tex;
}

void Game::AddAsteroid(class Asteroid* ast)
{
    mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(class Asteroid* ast)
{
    auto iter = std::find(mAsteroids.begin(),
                          mAsteroids.end(),
                          ast);
    if (iter != mAsteroids.end())
    {
        mAsteroids.erase(iter);
    }
}

void Game::Shutdown()
{
    UnloadData();
//    IMG_Quit();
//    SDL_DestoryRenderer(mRenderer);
    delete mSpriteVerts;
    mSpriteShader->Unload();
    delete mSpriteShader;
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::AddActor(class Actor* actor)
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

void Game::RemoveActor(class Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(),
                          mPendingActors.end(),
                          actor);
    if (iter != mPendingActors.end())
    {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    
    iter = std::find(mActors.begin(),
                     mActors.end(),
                     actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(class SpriteComponent* sprite)
{
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (;
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

void Game::RemoveSprite(class SpriteComponent* sprite)
{
    // スワップする必要なし
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Game::CreateSpriteVerts()
{
    float vertices[] = {
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,  // 左上
         0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // 右上
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // 右下
        -0.5f, -0.5f, 0.f, 0.0f, 1.0f   // 左下
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

bool Game::LoadShaders()
{
    mSpriteShader = new Shader();
    if (!mSpriteShader->Load(SHADER_DIR "Shaders/Sprite.vert"/*"Shaders/Transform.vert"*//*"Shaders/Basic.vert"*/, SHADER_DIR "Shaders/Sprite.frag"/*"Shaders/Basic.frag"*/))
    {
        return false;
    }
    mSpriteShader->SetActive();
    
    // 画面が1024x768という前提で単純なビュー射影行列を作成して設定している。
    Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
    mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
    
    return true;
}
