//
//  Game.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/28.
//

#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"

#include <unordered_map>
#include <string>
#include <vector>

#define ASSET_DIR "/Users/inoueshinichi/Desktop/MyGithub/GameProgrammingCpp/GPC_Ch08/"
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
    
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    
    class Texture* GetTexture(const std::string& fileName);
    
    
    void AddAsteroid(class Asteroid* ast);
    void RemoveAsteroid(class Asteroid* ast);
    std::vector<Asteroid*>& GetAsteroids() { return mAsteroids; }
    
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    
    void CreateSpriteVerts();
    bool LoadShaders();
    
    // テクスチャの連想配列
//    std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::unordered_map<std::string, class Texture*> mTextures;
    // アクター配列
    std::vector<Actor*> mActors;
    // 待機アクター配列
    std::vector<Actor*> mPendingActors;
    // スプライト・コンポーネント配列
    std::vector<SpriteComponent*> mSprites;
    
    
    /* OpenGL変数 */
    SDL_GLContext mContext; // コンテキスト
    class VertexArray* mSpriteVerts; // 頂点配列オブジェクトのポインタ
    class Shader* mSpriteShader;
    
    SDL_Window* mWindow;
    //SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;
    
    
    class Ship* mShip;
    std::vector<class Asteroid*> mAsteroids;
    
    /*入力システム*/
    class InputSystem* mInputSystem;
};


#endif /* Game_hpp */
