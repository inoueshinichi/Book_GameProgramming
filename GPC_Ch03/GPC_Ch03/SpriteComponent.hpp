//
//  SpriteComponent.hpp
//  GPC_Ch03
//
//  Created by Inoue Shinichi on 2022/03/18.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(Actor* owner, int drawOrder=100);
    virtual ~SpriteComponent();
    
    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);
    
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }
    
protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;
};

#endif /* SpriteComponent_hpp */
