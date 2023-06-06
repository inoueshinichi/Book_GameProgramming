//
//  Game.hpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.hpp"
#include "SoundEvent.hpp"

#define ASSETS_DIR "/Users/inoueshinichi/Desktop/MyGithub/Book_GameProgramming/GPC_Ch10/"
#define SHADERS_DIR ASSETS_DIR

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    class Renderer* GetRenderer() { return mRenderer; }
    class AudioSystem* GetAudioSystem() { return mAudioSystem; }
    class PhysWorld* GetPhysWorld() { return mPhysWorld; }
    
    // Game specific
    void AddPlane(class PlaneActor* plane);
    void RemovePlane(class PlaneActor* plane);
    std::vector<class PlaneActor*>& GetPlanes() { return mPlanes; }
    
private:
    void ProcessInput();
    void HandleKeyPress(int key);
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    
    class Renderer* mRenderer;
    class AudioSystem* mAudioSystem;
    class PhysWorld* mPhysWorld;
    
    Uint32 mTicksCount;
    bool mIsRunning;
    // Track if we're updating actors right now
    bool mUpdatingActors;
    
    // Game spacific
    std::vector<class PlaneActor*> mPlanes;
    class FPSActor* mFPSActor;
    class SpriteComponent* mCrosshair;
    SoundEvent mMusicEvent;
};

#endif /* Game_hpp */
