//
//  OrbitActor.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2023/01/25.
//

#ifndef OrbitActor_hpp
#define OrbitActor_hpp

#include "Actor.hpp"

class OrbitActor : public Actor
{
public:
    OrbitActor(class Game* game);
    ~OrbitActor() {}
    
    void ActorInput(const uint8_t* keyState) override;
    
    void SetVisible(bool visible);
    
private:
    class OrbitCamera* mCameraComp;
    class MeshComponent* mMeshComp;
};

#endif /* OrbitActor_hpp */
