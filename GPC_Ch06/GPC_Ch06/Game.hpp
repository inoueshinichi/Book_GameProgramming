//
//  Game.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/12.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.hpp"

#define ASSETS_DIR "/Users/inoueshinichi/Desktop/MyGithub/Book_GameProgramming/GPC_Ch06/"
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
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    
    class Renderer* mRenderer;
    
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;
    class CameraActor* mCameraActor;
};

#endif /* Game_hpp */
