//
//  Game.cpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#include "Game.hpp"
#include <algorithm>
#include "Renderer.hpp"
#include "AudioSystem.hpp"
#include "PhysWorld.hpp"
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "MeshComponent.hpp"
#include "FPSActor.hpp"
#include "PlaneActor.hpp"
#include "TargetActor.hpp"
#include "BallActor.hpp"

Game::Game()
    : mRenderer(nullptr)
    , mAudioSystem(nullptr)
    , mPhysWorld(nullptr)
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
    
    mRenderer = new Renderer(this);
    if (!mRenderer->Initialize(1024.0f, 768.0f))
    {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }
    
    mAudioSystem = new AudioSystem(this);
    if(!mAudioSystem->Initialize())
    {
        SDL_Log("Failed to initialize audio system");
        mAudioSystem->Shutdown();
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }
    
    mPhysWorld = new PhysWorld(this);
    
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

void Game::AddPlane(class PlaneActor *plane)
{
    mPlanes.emplace_back(plane);
}

void Game::RemovePlane(class PlaneActor *plane)
{
    auto iter = std::find(mPlanes.begin(), mPlanes.end(), plane);
    mPlanes.erase(iter);
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
                
            case SDL_KEYDOWN:
                if (!event.key.repeat)
                {
                    HandleKeyPress(event.key.keysym.sym);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                HandleKeyPress(event.button.button);
                break;
            default:
                break;
        }
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    
    for (auto actor : mActors)
    {
        actor->ProcessInput(state);
    }
}

void Game::HandleKeyPress(int key)
{
    switch (key)
    {
        case '-':
        {
            float volume = mAudioSystem->GetBusVolume("bus:/");
            volume = Math::Max(0.0f, volume - 0.1f);
            mAudioSystem->SetBusVolume("bus:/", volume);
            break;
        }
            
        case '=':
        {
            float volume = mAudioSystem->GetBusVolume("bus:/");
            volume = Math::Max(1.0f, volume + 0.1f);
            mAudioSystem->SetBusVolume("bus:/", volume);
            break;
        }
            
        case SDL_BUTTON_LEFT:
        {
            // Fire weapon
            mFPSActor->Shoot();
            break;
        }
        default:
            break;
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
    
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    
    for (auto pending : mPendingActors)
    {
        pending->ComputeWorldTransform();
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    
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
        delete actor;
    }
    
    mAudioSystem->Update(deltaTime);
}

void Game::GenerateOutput()
{
    mRenderer->Draw();
}

void Game::LoadData()
{
    Actor* a = nullptr;
    Quaternion q;
//    MeshComponent* mc = nullptr;
    
    // Setup floor
    const float start = -1250.0f;
    const float size = 250.0f;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            a = new PlaneActor(this);
            // xy [-1250,1000,250], z [-100]
            a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
        }
    }
    
    // Left/right walls
    q = Quaternion(Vector3::UnitX, Math::PiOver2);
    for (int i = 0; i < 10; ++i)
    {
        a = new PlaneActor(this);
        // x [-1250,-250,250], y [-1500], z [0]
        a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
        a->SetRotation(q);
        
        a = new PlaneActor(this);
        // x [-1250,-250,250], y [1500], z [0]
        a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
        a->SetRotation(q);
    }
    
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
    
    // Forward/back walls
    for (int i = 0; i < 10; ++i)
    {
        a = new PlaneActor(this);
        // x [-1500], y [-1250,1000,250], z [0]
        a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
        a->SetRotation(q);
        
        a = new PlaneActor(this);
        // x [1500], y [-1250,1000,250], z [0]
        a->SetPosition(Vector3(-start + size, start + i * size , 0.0f));
        a->SetRotation(q);
    }
    
    
    // Setup lights
    mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight& dir = mRenderer->GetDirectionalLight();
    dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
    
    // UI elements
    a = new Actor(this);
    a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
    SpriteComponent* sc = new SpriteComponent(a);
    sc->SetTexture(mRenderer->GetTexture(ASSETS_DIR "Assets/HealthBar.png"));
    
    a = new Actor(this);
    a->SetPosition(Vector3(-390.0f, 275.0f, 0.0f));
    a->SetScale(0.75f);
    sc = new SpriteComponent(a);
    sc->SetTexture(mRenderer->GetTexture(ASSETS_DIR "Assets/Radar.png"));
    
    a = new Actor(this);
    a->SetScale(2.0f);
    mCrosshair = new SpriteComponent(a);
    mCrosshair->SetTexture(mRenderer->GetTexture(ASSETS_DIR "Assets/Crosshair.png"));
    
    // Start music
    mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
    
    // Enable relative mouse mode for camera look
    SDL_SetRelativeMouseMode(SDL_TRUE);
    // Make an initial call to get relative to clear out
    SDL_GetRelativeMouseState(nullptr, nullptr);
    
    // Difference camera actor
    mFPSActor = new FPSActor(this);
    
    // Create target actors
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, 0.0f, 100.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, 0.0f, 400.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, -500.0f, 200.0f));
    a = new TargetActor(this);
    a->SetPosition(Vector3(1450.0f, 500.0f, 200.0f));
}

void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    
    if (mRenderer)
    {
        mRenderer->UnloadData();
    }
}

void Game::Shutdown()
{
    UnloadData();
    delete mPhysWorld;
    if (mRenderer)
    {
        mRenderer->Shutdown();
    }
    if (mAudioSystem)
    {
        mAudioSystem->Shutdown();
    }
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
    // Is it in pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    
    // Is it in actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}


