//
//  Font.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
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
    
    bool Load(const std::string& fileName);
    void Unload();
    
    class Texture* RenderText(const std::string& textKey,
                              const Vector3& color = Color::White,
                              int pointSize = 30);
    
private:
    std::unordered_map<int, TTF_Font*> mFontData;
    class Game* mGame;
};

#endif /* Font_hpp */
