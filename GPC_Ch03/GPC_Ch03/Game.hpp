//
//  Game.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"

#include <unordered_map>
#include <string>
#include <vector>

#define ASSETS_DIR "/Users/inoueshinichi/Desktop/MyGithub/Book_GameProgramming/GPC_Ch03/"


class Actor;
class SpriteComponent;
class Ship;
class Asteroid;


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
    
    // このゲーム特有
    void AddAsteroid(Asteroid* ast);
    void RemoveAsteroid(Asteroid* ast);
    std::vector<Asteroid*>& GetAsteroids() { return mAsteroids; }
    
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    // テクスチャの連想配列
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    // アクター配列
    std::vector<Actor*> mActors;
    // 待機アクター配列
    std::vector<Actor*> mPendingActors;
    // スプライト・コンポーネント配列
    std::vector<SpriteComponent*> mSprites;
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;
    
    // このゲーム特有
    Ship* mShip;
    std::vector<Asteroid*> mAsteroids;
};

#endif /* Game_hpp */
