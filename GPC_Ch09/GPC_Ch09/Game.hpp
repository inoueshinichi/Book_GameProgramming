//
//  Game.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.hpp"
#include "SoundEvent.hpp"

#define ASSETS_DIR "/Users/inoueshinichi/Desktop/MyGithub/Book_GameProgramming/GPC_Ch09/"

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
    
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;
    
    // Game-sepcific code
    class FPSActor* mFPSActor;
    class FollowActor* mFollowActor;
    class OrbitActor* mOrbitActor;
    class SplineActor* mSplineActor;
    class Actor* mStartSphere;
    class Actor* mEndSphere;
    class SpriteComponent* mCrosshair;
    SoundEvent mMusicEvent;
    SoundEvent mReverbSnap;
    void ChangeCamera(int mode);
};

#endif /* Game_hpp */
