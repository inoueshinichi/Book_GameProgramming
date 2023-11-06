//
//  Game.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/10/24.
//

#ifndef Game_hpp
#define Game_hpp

#include <unordered_map>
#include <string>
#include <vector>
#include "Math.hpp"
#include "SoundEvent.hpp"
#include <SDL_types.h>

#define ASSETS_DIR "/Users/inoueshinichi/Desktop/MyGithub/Book_GameProgramming/GPC_Ch12/"
#define SHADERS_DIR ASSETS_DIR

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    class Renderer* GetRenderer() {
        return mRenderer;
    }
    
    class AudioSystem* GetAudioSystem() {
        return mAudioSystem;
    }
    
    class PhysWorld* GetPhysWorld() {
        return mPhysWorld;
    }
    
    class HUD* GetHUD() {
        return mHUD;
    }
    
    // UI stack
    const std::vector<class UIScreen*>& GetUIStack() {
        return mUIStack;
    }
    
    void PushUI(class UIScreen* screen);
    
    
    class FollowActor* GetPlayer() {
        return mFollowActor;
    }
    
    // Game state
    enum GameState {
        EGameplay,
        EPaused,
        EQuit
    };
    
    GameState GetState() const {
        return mGameState;
    }
    
    void SetState(GameState state) {
        mGameState = state;
    }
    
    // Font
    class Font* GetFont(const std::string& fileName);
    
    void LoadText(const std::string& fileName);
    const std::string& GetText(const std::string& key);
    
    // Skelton
    class Skeleton* GetSkeleton(const std::string& fileName);
    
    // Animation
    class Animation* GetAnimation(const std::string& fileName);
    
    // Game-specific
    void AddPlane(class PlaneActor* plane);
    
    void RemovePlane(class PlaneActor* plane);
    
    std::vector<class PlaneActor*>& GetPlanes() {
        return mPlanes;
    }
    
private:
    
    void ProcessInput();
    void HandleKeyPress(int key);
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    // Actors
    std::vector<class Actor*> mActors;
    
    // Pending actors
    std::vector<class Actor*> mPendingActors;
    
    // UI screens
    std::vector<class UIScreen*> mUIStack;
    
    // Map of fonts
    std::unordered_map<std::string, class Font*> mFonts;
    
    // Map of skeletons
    std::unordered_map<std::string, class Skeleton*> mSkeletons;
    
    // Map of animations
    std::unordered_map<std::string, class Animation*> mAnims;
    
    // Map of text localization
    std::unordered_map<std::string, std::string> mText;
    
    // Game update
    GameState mGameState;
    Uint32 mTicksCount;
    bool mUpdatingActors;
    
    // Game functions
    class Renderer* mRenderer;
    class AudioSystem* mAudioSystem;
    class PhysWorld* mPhysWorld;
    class HUD* mHUD;
    
    // Game-specific
    class FollowActor* mFollowActor;
    std::vector<class PlaneActor*> mPlanes;
    class SpriteComponent* mCrosshair;
    SoundEvent mMusicEvent;
};

#endif /* Game_hpp */
