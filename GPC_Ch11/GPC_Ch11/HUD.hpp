//
//  HUD.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/29.
//

#ifndef HUD_hpp
#define HUD_hpp

#include "UIScreen.hpp"
#include <vector>

class HUD : public UIScreen
{
public:
    HUD(class Game* game);
    ~HUD();
    
    void Update(float deltaTime) override;
    void Draw(class Shader* shader) override;
    
    void AddTargetComponent(class TargetComponent* tc);
    void RemoveTargetComponent(class TargetComponent* tc);
    
protected:
    void UpdateCrosshair(float deltaTime);
    void UpdateRadar(float deltaTime);
    
    class Texture* mHealthBar;
    class Texture* mRadar;
    class Texture* mCrosshair;
    class Texture* mCrosshairEnemy;
    class Texture* mBlipTex;
    class Texture* mRadarArrow;
    
    // All the target components in the game
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
