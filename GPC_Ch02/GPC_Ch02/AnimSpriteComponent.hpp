//
//  AnimSpriteComponent.hpp
//  GPC_Ch02
//
//  Created by Inoue Shinichi on 2022/03/15.
//

#ifndef AnimSpriteComponent_hpp
#define AnimSpriteComponent_hpp

#include "SpriteComponent.hpp"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(Actor* owner, int drawOrder = 100);
    // フレームごとにアニメーションを更新する(Componentからのオーバーライド)
    void Update(float deltaTime) override;
    // アニメーションに使うテクスチャを設定する
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    // アニメーションのFPSを設定/取得
    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }
    
private:
    // アニメーションでのすべてのテクスチャ
    std::vector<SDL_Texture*> mAnimTextures;
    // 現在表示しているフレーム
    float mCurrFrame;
    // アニメーションのフレームレート
    float mAnimFPS;
};
#endif /* AnimSpriteComponent_hpp */
