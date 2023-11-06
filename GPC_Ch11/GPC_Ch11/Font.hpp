//
//  Font.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/13.
//

#ifndef Font_hpp
#define Font_hpp

#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include "Math.hpp"

class Font
{
public:
    Font(class Game* game);
    ~Font();
    
    // Load/unload from a file
    bool Load(const std::string& fileName);
    void Unload();
    
    // Given string and this font, draw to a texture
    class Texture* RenderText(const std::string& textKey,
                              const Vector3& color = Color::White,
                              int pointSize = 30);
    
private:
    // Map of point sizes to font data
    std::unordered_map<int, TTF_Font*> mFontData;
    class Game* mGame;
};

#endif /* Font_hpp */
