//
//  Texture.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#include "Texture.hpp"
#include <SOIL.h>
#include <GL/glew.h>
#include <SDL.h>

Texture::Texture()
    : mTextureID(0)
    , mWidth(0)
    , mHeight(0)
{}

Texture::~Texture()
{}

bool Texture::Load(const std::string& fileName)
{
    int channels = 0;
    
    unsigned char* image = SOIL_load_image(fileName.c_str(),
                                           &mWidth,
                                           &mHeight,
                                           &channels,
                                           SOIL_LOAD_AUTO);
    
    if (image == nullptr)
    {
        SDL_Log("SOIL failed to load image %s: %s",
                fileName.c_str(), SOIL_last_result());
        return false;
    }
    
    int format = GL_RGB;
    if (channels == 4)
    {
        format = GL_RGBA;
    }
    
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0, format,
                 mWidth, mHeight,
                 0, format, GL_UNSIGNED_BYTE,
                 image);
    
    SOIL_free_image_data(image);
    
    // Enable linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return true;
}

void Texture::Unload()
{
    glDeleteTextures(1, &mTextureID);
}

void Texture::CreateFromSurface(struct SDL_Surface *surface)
{
    mWidth = surface->w;
    mHeight = surface->h;
    
    // gen a GL texture
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D,
                 0, GL_RGBA,
                 mWidth, mHeight,
                 0, GL_BGRA, GL_UNSIGNED_BYTE,
                 surface->pixels);
    
    // Enable linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

