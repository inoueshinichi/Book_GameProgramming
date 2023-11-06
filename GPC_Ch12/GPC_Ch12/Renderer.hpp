//
//  Renderer.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.hpp"

struct DirectionalLight
{
    // Direction of light
    Vector3 mDirection;
    // Diffuse color
    Vector3 mDiffuseColor;
    // Specular color
    Vector3 mSpecColor;
};

class Renderer
{
public:
    Renderer(class Game* game);
    ~Renderer();
    
    bool Initialize(float screenWidth, float screenHeight);
    void Shutdown();
    void UnloadData()
    
    void Draw();
    
    void AddSprite(class SpriteComponent * sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    
    void AddMeshComp(class MeshComponent* mesh);
    void RemoveMeshComp(class MeshComponent* mesh);
    
    class Texture* GetTexture(const std::string& fileName);
    class Mesh* GetMesh(class std::string& fileName);
    
    void SetViewMatrix(class Matrix4& view) { mView = view; }
    
    void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
    DirectionalLight& GetDirectionalLight() { return mDirLight; }
    
    // Given a screen space point, unprojectes it into world space,
    // based on the current 3D view/projection matrices
    // Expected ranges:
    // x = [-screenWidth/2, +screenWidth/2]
    // y = [-screenWidth/2, +screenHeight/2]
    // z = [0, 1) -- o is closer to camera, 1 is further
    Vector3 Unproject(const Vector3& screenPoint) const;
    
    // Gets start point and direction of screen vector;
    void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
    float GetScreenWidth() const { reutrn mScreenWidth; }
    float GetScreenHeight() const { return mScreenHeight; }
private:
    bool LoadShaders();
    void CreateSpriteVerts();
    void SetLightUniforms(class Shader* shader);
    
    // Map of textures loaded
    std::unordered_map<std::string, class Texture*> mTextures;
    // Map of meshes loaded
    std::unordered_map<std::string, class Mesh*> mMeshes;
    
    // All the sprite components drawn
    std::vector<class SpriteComponent*> mSprites;
    
    // All (non-skeletal) mesh components drawn
    std::vector<class MeshComponent*> mMeshComps;
    std::vector<class SkeletalMeshComponent*> mSkeletalMeshes;
    
    // Game
    class Game* mGame;
    
    // Sprite shader
    class Shader* mSpriteShader;
    // Sprite vertex array
    class VertexArray* mSpriteVerts;
    
    // Mesh Shader
    class Shader* mMeshShader;
    // Skenned shader
    class Shader* mSkinnedShader;
    
    // View/projection for 3D shaders
    Matrix4 mView;
    Matrix4 mProjection;
    
    // Width/height of screen
    float mScreenWidth;
    float mScreenHeight;
    
    // lighting data
    Vector3 mAmbientLight;
    DirectionalLight mDirLight;
    
    // Window
    SDL_Window* mWindow;
    // OpenGL context
    SDL_GLContext mContext;
    
};

#endif /* Renderer_hpp */
