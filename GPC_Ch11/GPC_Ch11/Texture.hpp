//
//  Texture.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/13.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();
    
    bool Load(const std::string& fileName);
    void Unload();
    void CreateFromSurface(struct SDL_Surface* surface);
    
    void SetActive();
    
    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }
private:
    unsigned int mTextureID;
    int mWidth;
    int mHeight;
};

#endif /* Texture_hpp */
