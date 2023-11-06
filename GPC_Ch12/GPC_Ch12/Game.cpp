//
//  Game.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/10/24.
//

#include "Game.hpp"

#include "Renderer.hpp"
#include "AudioSystem.hpp"
#include "PhysWorld.hpp"
#include "Actor.hpp"
#include "UIScreen.hpp"
#include "HUD.hpp"
#include "PauseMenu.hpp"
#include "Font.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include "MeshComponent.hpp"
#include "FollowActor.hpp"
#include "PlaneActor.hpp"
#include "TargetActor.hpp"
#include "BallActor.hpp"
#include "Skeleton.hpp"
#include "Animation.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

Game::Game()
    : mRenderer(nullptr)
    , mAudioSystem(nullptr)
    , mPhysWorld(nullptr)
    , mGameState(EGameplay)
    , mUpdatingActors(false)
{}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    // Renderer
    mRenderer = new Renderer(this);
    if (!mRenderer->Initialize(1024.0f, 768.0f)) {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }
    
    // AudioSystem
    mAudioSystem = new AudioSystem(this);
    if (!mAudioSystem->Initialize()) {
        SDL_Log("Failed to initialize audio system");
        mAudioSystem->Shutdown();
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }
    
    // PhysWorld
    mPhysWorld = new PhysWorld(this);
    
    // SDL_ttf
    if (TTF_Init() != 0) {
        SDL_Log("Failed to initialize SDL_ttf");
        return false;
    }
    
    // 初期データ
    LoadData();
    
    mTicksCount = SDL_GetTicks();
    
    return true;
}

void Game::RunLoop() {
    while (mGameState != EQuit) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    // イベントキューから溜まっているイベントを回収
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            // ゲーム停止メッセージ
            case SDL_QUIT:
            {
                mGameState = EQuit;
                break;
            }
            
                
            // キーボード入力メッセージ
            case SDL_KEYDOWN:
            {
                if (!event.key.repeat) {
                    if (mGameState == EGameplay) {
                        HandleKeyPress(event.key.keysym.sym);
                    } else if (!mUIStack.empty()) {
                        mUIStack.back()->HandleKeyPress(event.key.keysym.sym);
                    }
                }
                break;
            }
            
                
            // マウスクリック
            case SDL_MOUSEBUTTONDOWN:
            {
                if (mGameState == EGameplay) {
                    HandleKeyPress(event.button.button);
                } else if (!mUIStack.empty()) {
                    mUIStack.back()->HandleKeyPress(event.button.button);
                }
                break;
            }
            
            default:
                break;
        }
    } // while
    
    // Actorに対して個別に入力
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (mGameState == EGameplay) {
        for (auto actor : mActors) {
            if (actor->GetState() == Actor::EActive) {
                actor->ProcessInput(state);
            }
        }
    } else if (!mUIStack.empty()) {
        // UIスタックが溜まっていたら最上位UIで入力処理
        mUIStack.back()->ProcessInput(state);
    }
}

void Game::HandleKeyPress(int key) {
    switch (key)
    {
        case SDLK_ESCAPE:
        {
            // Create pause menu
            new PauseMenu(this);
            break;
        }
        
        case '-':
        {
            // master volume -
            float volume = mAudioSystem->GetBusVolume("bus:/");
            volume = Math::Max(0.0f, volume - 0.1f);
            mAudioSystem->SetBusVolume("bus:/", volume);
            break;
        }
        
            
        case '=':
        {
            // master volume +
            float volume = mAudioSystem->GetBusVolume("bus:/");
            volume = Math::Max(1.0f, volume + 0.1f);
            mAudioSystem->SetBusVolume("bus:/", volume);
            break;
        }
        
            
        case '1':
        {
            // Load English text
            LoadText(ASSETS_DIR "Assets/English.gptext");
            break;
        }
        
        case '2':
        {
            LoadText(ASSETS_DIR "Assets/Russian.gptext");
            break;
        }
        
        default:
            break;
    }
}

void Game::UpdateGame() {
    // Compute delta time
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks(); // update ticks
    
    if (mGameState == EGameplay) {
        // Update actors
        mUpdatingActors = true;
        for (auto actor : mActors) {
            actor->Update(deltaTime);
        }
        mUpdatingActors = false;
        
        // Move any pending actors to mActors
        for (auto pending : mPendingActors) {
            pending->ComputeWorldTransform();
            mActors.emplace_back(pending);
        }
        mPendingActors.clear();
        
        // Delete dead actors
        std::vector<Actor*> deadActors;
        for (auto actor : mActors) {
            if (actor->GetState() == Actor::EDead) {
                deadActors.emplace_back(actor);
            }
        }
        
        for (auto actor : deadActors) {
            delete actor;
        }
    } // if (mGameState == EGameplay)
    
    // Update audio system
    mAudioSystem->Update(deltaTime);
    
    // Update UI screens
    for (auto ui : mUIStakc) {
        if (ui->GetState() == UIScreen::EActive) {
            ui->Update(deltaTime);
        }
    }
    auto iter = mUIStack.begin();
    while (iter != mUIStack.end()) {
        if ((*iter)->GetState() == UIScreen::EClosing) {
            delete *iter;
            iter = mUIStack.erase(iter);
        } else {
            ++iter;
        }
    }
}

void Game::GenerateOutput() {
    mRenderer->Draw();
}

void Game::Shutdown() {
    UnloadData();
    TTF_Quit();
    delete mPhysWorld;
    if (mRenderer) {
        mRenderer->Shutdown();
    }
    if (mAudioSystem) {
        mAudioSystem->Shutdown();
    }
    SDL_Quit();
}


// Add/Remove actors

void Game::AddPlane(class PlaneActor *plane)
{
    mPlanes.emplace_back(plane);
}

void Game::RemovePlane(class PlaneActor *plane) {
    auto iter = std::find(mPlanes.begin(), mPlanes.end(), plane);
    mPlanes.erase(iter);
}

void Game::AddActor(class Actor *actor)
{
    if (mUpdateActors) {
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(class Actor *actor) {
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

// Push to UIStack
void Game::PushUI(class UIScreen *screen)
{
    mUIStack.emplace_back(screen);
}

// Font
Font* Game::GetFont(const std::string &fileName) {
    auto iter = mFonts.find(fileName);
    if (iter != mFonts.end())
    {
        return iter->second;
    }
    else {
        // 生成を試みる
        Font* font = new Font(this);
        if (font->Load(fileName))
        {
            mFonts.emplace(fileName, font);
        } else {
            font->Unload();
            delete font;
            fotn = nullptr;
        }
        return font;
    }
}


// Text
void Game::LoadText(const std::string &fileName)
{
    // Clear the existing map, if already loaded
    mText.clear();
    
    // Try to open the file
    std::ifstream file(fileName)
    if (!file.is_open()) {
        SDL_Log("Text file %s not found", fileName.c_str());
        return;
    }
    
    // Read the entire file to a string stream
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    
    // Open this file in rapidJSON
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);
    if (!doc.IsObject()) {
        SDL_Log("Text file %s is not valid JSON", fileName.c_str());
        return;
    }
    
    // Parse the text map
    const rapidjson::Value& actions = doc["TextMap"];
    for (rapidjson::Value::ConstMemberIterator iter = actions.MemberBegin();
         iter != actions.MemberEnd();
         ++iter)
    {
        if (iter->name.IsString() && iter->value.IsString())
        {
            mText.emplace(iter->name.GetString(), iter->value.GetString());
        }
    }
}

const std::string& Game::GetText(const std::string &key)
{
    static std::string errorMsg("**KEY NOT FOUND**");
    
    auto iter = mText.find(key);
    if (iter != mText.end()) {
        return iter->second;
    } else {
        return errorMsg;
    }
}


// 初期データ

void Game::LoadData()
{
    // Load English text
    LoadText(ASSETS_DIR "Assets/English.gptext");
    
    Actor* a = nullptr;
    Quaternion q;
    MeshComponent* mc = nullptr;
    
    // Floor
    const float start = -1250.0f;
    const float size = 250.0f;
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a = new PlaneActor(this);
            a->SetPosition(Vector3(start + i * size, start + j * size, -100));
        }
    }
    
    // Walls of left/right
    q = Quaternion(Vector3::UnixX, Math::PiOver2);
    for (int i = 0; i < 10; i++)
    {
        // Left
        a = new PlaneActor(this);
        a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
        a->SetRotation(q);
        
        // Right
        a = new PlaneActor(this);
        a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
        a->SetRotation(q);
    }
    
    // Walls of forward/backword
    q = Quaternion::Concatenate(q, Quaternion::(Vector3::UnitZ, Math::PiOver2));
    for (int i = 0; i < 10; i++)
    {
        // Forward
        a = new PlaneActor(this);
        a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
        a->SetRotation(q);
        
        // Backward
        a = new PlaneActor(this);
        a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
        a->SetRotation(q);
    }
    
    // Lighting
    mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight& dir = mRenderer->GetDirectionalLight();
    dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
    
    // UI
    mHUD = new HUD(this);
    
    
    // Music
    mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
    
    // Elable relative mouse mode for camera look
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    // Make an initial call to get relative to clear out
    SDL_GetRlativeMouseState(nullptr, nullptr);
    
    // Different camera actors
    mFollowActor = new FollowActor(this);
    
    // Create target actors
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, 0.0f, 100.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, 0.0f, 400.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, -500.0f, 200.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, 500.0f, 200.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(0.0f, -1450.0f, 200.0f));
    a->SetRotation(Quaternion(Vector3::UnitZ, Math::PiOver2));
    a = new TargetActor(this);
    a->SetPosition(Vector3(0.0f, 1450.0f, 200.0f));
    a->SetRotation(Quaternion(Vector3::UnitZ, -Math::PiOver2));
}

void Game::UnloadData()
{
    // Delete actors
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    
    // Delete UI screens
    while (!mUIStack.empty())
    {
        delete mUIStack.back();
        mUIStack.pop_back();
    }
    
    // Delete Renderer
    if (mRenderer)
    {
        mRenderer->UnloadData();
    }
    
    // Delete fonts
    for (auto f : mFonts)
    {
        f.second->Unload();
        delete f.second;
    }
    
    // Delete skeletons
    for (auto s : mSkeletons)
    {
        delete s.second;
    }
    
    // Delete animations
    for (auto a : mAnims)
    {
        delete a.second;
    }
}

// Skeleton
Skeleton* Game::GetSkeleton(const std::string& fileName)
{
    auto iter = mSkeletons.find(fileName);
    if (iter != mSkeletons.end())
    {
        return iter->second;
    }
    else {
        Skeleton* sk = new Skeleton();
        if (sk->Load(fileName))
        {
            mSkeletons.emplace(fileName, sk);
        }
        else {
            delete sk;
            sk = nullptr;
        }
        return sk;
    }
}

// Animation
Animation* Game::GetAnimation(const std::string &fileName)
{
    auto iter = mAnims.find(fileName);
    if (iter != mAnims.end())
    {
        return iter->second;
    }
    else {
        Animation* anim = new Skeleton();
        if (anim->Load(fileName))
        {
            mAnims.emplace(fileName, anim);
        }
        else {
            delete anim;
            anim = nullptr;
        }
        return anim;
    }
}


