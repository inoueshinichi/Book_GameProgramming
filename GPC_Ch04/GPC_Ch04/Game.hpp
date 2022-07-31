//
//  Game.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/27.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.hpp"

#define ASSET_DIR "/Users/inoueshinichi/Desktop/MyGithub/GameProgrammingCpp/GPC_Ch04/"


class Actor;
class SpriteComponent;
class Enemy;
class Grid;

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    
    SDL_Texture* GetTexture(const std::string& fileName);
    
    Grid* GetGrid() { return mGrid; }
    std::vector<Enemy*>& GetEnemies() { return mEnemies; }
    Enemy* GetNearestEnemy(const Vector2& pos);
    
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    
    std::vector<Actor*> mActors;
    
    std::vector<Actor*> mPendingActors;
    
    std::vector<SpriteComponent*> mSprites;
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;
    
    // Chapter04固有
    std::vector<Enemy*> mEnemies;
    Grid* mGrid;
    float mNextEnemy;
};

#endif /* Game_hpp */
