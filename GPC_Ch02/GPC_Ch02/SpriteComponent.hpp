//
//  SpriteComponent.hpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/15.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "SDL.h"
#include "Component.hpp"
#include "Actor.hpp"

class Actor;

class SpriteComponent : public Component
{
public:
    // 描画順序(drawOrder)が低いほど遠くに描画される
    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    
    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);
    
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }
    
protected:
    // 描画するテクスチャ
    SDL_Texture* mTexture;
    // 画家のアルゴリズムで使う描画順序
    int mDrawOrder;
    // テクスチャの幅と高さ
    int mTexWidth;
    int mTexHeight;
};

#endif /* SpriteComponent_hpp */
