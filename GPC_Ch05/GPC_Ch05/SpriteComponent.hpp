//
//  SpriteComponent.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include "Shader.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* owner, int updateOrder = 100);
    virtual ~SpriteComponent();
    
//    virtual void Draw(SDL_Renderer* renderer);
    virtual void Draw(Shader* shader);
//    virtual void SetTexture(SDL_Texture* texture);
    virtual void SetTexture(class Texture* texture);
    
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }
    
protected:
//    SDL_Texture* mTexture;
    class Texture* mTexture;
    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;
};

#endif /* SpriteComponent_hpp */
