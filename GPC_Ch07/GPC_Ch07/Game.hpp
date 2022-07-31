//
//  Game.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/12.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.hpp"
#include "SoundEvent.hpp"

#define ASSET_DIR "/Users/inoueshinichi/Desktop/MyGithub/GameProgrammingCpp/GPC_Ch07/"
#define SHADER_DIR ASSET_DIR

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
    
    class CameraActor* mCameraActor;
    SoundEvent mMusicEvent;
    SoundEvent mReverbSnap;
};

#endif /* Game_hpp */
