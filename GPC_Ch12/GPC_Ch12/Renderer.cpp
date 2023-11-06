//
//  Renderer.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#include "Renderer.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <algorithm>
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "SpriteComponent.hpp"
#include "MeshComponent.hpp"
#include "UIScreen.hpp"
#include "Game.hpp"
#include <GL/glew.h>
#include "SkeletalMeshComponent.hpp"

Renderer::Renderer(Game* game)
    : mGame(game)
    , mSpriteShader(nullptr)
    , mMeshShader(nullptr)
    , mSkinnedShader(nullptr)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;
    
    // Set OpenGL attributes
    // Use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // OpenGL 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    // Request a color buffer with 8-bits per RGBA channels
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    // main window
    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 12)",
                               100,
                               100,
                               static_cast<int>(mScreenWidth),
                               static_cast<int>(mScreenHeight),
                               SDL_WINDOW_OPENGL);
    
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    // Create an OpenGL context
    mContext = SDL_GL_CreateContext(mWindow);
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }
    
    // On some platforms, GLEW will emit a benign error code,
    // so clear it
    glGetError();
    
    // Make sure we can create/compile shaders
    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }
    
    // Create quad for drawing sprites
    CreateSpriteVerts();

    return true;
}

void Renderer::Shutdown()
{
    delete mSpriteVerts;
    mSpriteShader->Unload();
    delete mSpriteShader;
    mMeshShader->Unload();
    delete mMeshShader;
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
    //Destory textures
    for (auto i : mTextures)
    {
        i.second->Unload();
        delete i.second;
    }
    mTextures.clear();
    
    // Destroy meshes
    for (auto i : mMeshes)
    {
        i.second->Unload();
        delete i.second;
    }
    mMeshes.clear();
}

void Renderer::Draw()
{
    // Set the clear color to light grey
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // メッシュ描画用
    // Draw mesh components
    // Enable depth buffering/disable alpha blend
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    
    // Set the mesh shader active
    mMeshShader->SetActive();
    // Update view-porojection matrix
    mMeshShader->SetMatrixUniform("uViewPorj", mView * mProjection);
    
    // Update lighting uniforms
    SetLightUniforms(mMeshShader);
    for (auto mc : mMeshComps)
    {
        if (mc->GetVisible())
        {
            mc->Draw(mMeshShader);
        }
    }
    
    // スキン描画用
    mSkinnedShader->SetActive();
    // Update view-projection matrix
    mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
    // Update lighting uniforms
    SetLightUniforms(mSkinnedShader);
    for (auto sk : mSkeletalMeshes)
    {
        if (sk->GetVisible())
        {
            sk->Draw(mSkinnedShader);
        }
    }
    
    // スプライト描画用
    glDisable(GL_DEPTH_TEST);
    // アルファブレンディングモードを有効
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                        GL_ONE, GL_ZERO);
    
    // set shader/vao as actie
    mSpriteShader->SetActie();
    mSpriteVerts->SetActive();
    for (auto sprite : mSprites)
    {
        if (sprite->GetVisible())
        {
            sprite->Draw(mSpriteShader);
        }
    }
    
    // Draw any UI screens
    for (auto ui : mGame->GetUIStack())
    {
        ui->Draw(mSpriteShader);
    }
    
    // Swap the buffers
    SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    
    // Inserts element before posiiton of iterator
    mSprites.insert(iter, sprite);
}


void Renderer::RemoveSprite(SpriteComponent * sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Renderer::AddMeshComp(class MeshComponent *mesh)
{
    if (mesh->GetIsSkeletal())
    {
        // ダウンキャスト
        SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
        mSkeletalMeshes.emplace_back(sk);
    }
    else {
        mMeshComps.emplace_back(mesh);
    }
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
    if (mesh->GetIsSkeletal())
    {
        SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
        auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(),
                              mesh);
        mSkeletalMeshes.erase(iter);
    }
    else
    {
        auto iter std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
        mMeshComps.erase(iter);
    }
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
    Texture* tex = nullptr;
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        tex = new Texture();
        if (tex->Load(fileName))
        {
            mTextures.emplace(fileName, tex);
        }
        else {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
    Mesh* m = nullptr;
    auto iter = mMeshes.find(fileName);
    if (iter != mMeshes.end())
    {
        m = iter->second;
    }
    else
    {
        m = new Mesh();
        if (m->Load(fileName, this)) // MeshクラスにRendererクラスを注入する(依存性の注入)
        {
            mMeshes.emplace(fileName, m);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

bool Renderer::LoadShaders()
{
    // スプライト用
    mSpriteShader = new Shader();
    if (!mSpriteShader->Load(SHADERS_DIR "Shaders/Sprite.vert",
                             SHADERS_DIR "Shaders/Sprite.frag"))
    {
        return false;
    }
    mSpriteShader->SetActive();
    Matrix4 viewProj = Matrix4::CreateSimpleView(mScreenWidth, mScreenHeight);
    mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
    
    // 基本メッシュ用
    mMeshShader = new Shader();
    if (!mMeshShader->Load(SHADERS_DIR "Shaders/Phong.vert",
                           SHADERS_DIR "Shaders/Phong.frag"))
    {
        return false;
    }
    
    mMeshShader->SetActive();
    mView = Matrix4::CreateLookAt(/*camera pos*/Vector3::Zero,
                                  /*eye dir*/Vector3::UnitX,
                                  /*camera up*/Vector3::UnitZ);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
                                                mScreenWidth,
                                                mScreenHeight,
                                                /*near*/10.0f,
                                                /*far*/10000.0f);
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
    
    
    // スキン用
    mSkinnedShader = new Shader();
    if (!mSkinnedShader->Load(SHADERS_DIR "Shaders/Skinned.vert",
                              SHADERS_DIR "Shaders/Phong.frag"))
    {
        return false;
    }
    mSkinnedShader->SetActive();
    mView = Matrix4::CreateLookAt(/*camera pos*/Vector3::Zero,
                                  /*eye dir*/Vector3::UnitX,
                                  /*camera up*/Vector3::UnitZ);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
                                                mScreenWidth,
                                                mScreenHeight,
                                                /*near*/10.0f,
                                                /*far*/10000.0f);
    mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
    
    return true;
}

void Renderer::CreateSpriteVerts()
{
    float vertices[] = {
        /*x*/-0.5f, /*y*/0.5f, 0.f, 0.f, 0.f, 0.0f, 0.0f, // top left
        /*x*/0.5f, /*y*/0.5f, 0.f, 0.f, 0.f, 1.0f, 0.0f, // top right
        /*x*/0.5f, /*y*/-0.5f, 0.f, 0.f, 0.f, 1.0f, 1.0f, // bottom right
        /*x*/-0.5f, /*y*/-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.0f // bottom left
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    mSpriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::SetLightUniforms(Shader * shader)
{
    // camera pos is from inverted view
    Matrix4 invView = mView;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTraslation());
    // Ambient light (環境光)
    shader->SetVectorUniform("uAmbientLight", mAmbientLight);
    // Directional light (平行光)
    shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
    // 拡散反射色
    shader->SetVectorUniform("uDirLight.mDiffuseColor", mDirLight.mDiffuseColor);
    // 鏡面反射色
    shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
    // convert screen point to device coordinates (between -1 and +1)
    Vector3 deviceCoord = screenPoint;
    deviceCoord.x /= (mScreenWidth) * 0.5f;
    deviceCoord.y /= (mScreenHeight) * 0.5f;
    
    // transform vector by unprojection matrix
    Matrix4 unprojection = mView * mProjection;
    unprojection.Invert();
    return Vector3::TransformWithPerspDiv(deviceCoord, unprojection);
}

void Renderer::GetScreenDirection(Vector3& outStart, Vector3& outDir) const
{
    // get start point (in center of screen on near plane)
    Vector3 screenPoint(0.f, 0.f, 0.f);
    outStart = Unproject(screenPoint);
    
    // Get end point (in center of screen between near and far)
    screenPoint.z = 0.9f; // NDC
    Vector3 end = Unproject(screenPoint);
    
    // Get direction vector
    outDir = end - outStart;
    
    // 正規化
    outDir.Normalize();
}

