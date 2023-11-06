//
//  HUD.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#ifndef HUD_hpp
#define HUD_hpp

#include "UIScreen.hpp"
#include <vector>

class HUD : public UIScreen
{
public:
  // lower draw order corresponds with further back
    HUD(class Game* game);
    ~HUD();
    
    void Udpate(float deltaTime) override;
    void Draw(class Shader* shader) override;
    
    void AddTargetComponent(class TargetComponent* tc);
    void RemoveTargetComponent(class TargetComponent* tc);
    
protected:
    void UpdateCrosshair(float deltaTime);
    void UpdateRader(float deltaTime);
    
    class Texture* mHealthBar;
    class Texture* mRader;
    class Texture* mCrosshair;
    class Texture* mCrosshairEnemy;
    class Texture* mBlipTex;
    class Texture* mRadarArrow;
    
    // all the target compoennts in the game
    std::vector<class TargetComponent*> mTargetComps;
    // 2D offsets of blips relative to radar
    std::vector<Vector2> mBlips;
    // Adjust range of radar and radius
    float mRadarRange;
    float mRadarRadius;
    // Whether the crosshair targets an enemy
    bool mTargetEnemy;
};

#endif /* HUD_hpp */
