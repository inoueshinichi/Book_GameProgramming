//
//  SpriteComponent.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
public:
    // (Lower draw order corresponds with further back)
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    
    virtual void Draw(class Shader* shader);
    virtual void SetTexture(class Texture* texture);
    
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }
    
    void SetVisible(bool visible) { mVisible = visible; }
    bool GetVisible() const { return mVisible; }
    
protected:
    class Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
    bool mVisible;
};

#endif /* SpriteComponent_hpp */
