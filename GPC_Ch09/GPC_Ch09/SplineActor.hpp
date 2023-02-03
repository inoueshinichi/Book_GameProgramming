//
//  SplineActor.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/01/14.
//

#ifndef SplineActor_hpp
#define SplineActor_hpp

#include "Actor.hpp"

class SplineActor : public Actor
{
public:
    SplineActor(class Game* game);
    
    void ActorInput(const uint8_t* keys) override;
    
    void RestartSpline();
private:
    class SplineCamera* mCameraComp;
};

#endif /* SplineActor_hpp */
