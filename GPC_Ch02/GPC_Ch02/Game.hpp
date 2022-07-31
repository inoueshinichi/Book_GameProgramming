//
//  Game.hpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/13.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

#define ASSET_DIR "/Users/inoueshinichi/Desktop/MyGithub/GameProgrammingCpp/GPC_Ch02/"

// 前方宣言
class Actor;
class SpriteComponent;
class Ship;

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    
    SDL_Texture* GetTexture(const std::string& fileName);
    
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    // テクスチャ用連想配列
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    
    // ゲーム内のアクティブなActors
    std::vector<Actor*> mActors;
    // ゲーム内の待ち状態にあるActors
    std::vector<Actor*> mPendingActors;
    // 描画するスプライトComponent
    std::vector<SpriteComponent*> mSprites;
    
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
    
    // Actorが現在更新中かを示すフラグ
    bool mUpdatingActors;
    
    // このゲーム特有
    Ship* mShip;
    
};

#endif /* Game_hpp */
