//
//  PlaneActor.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef PlaneActor_hpp
#define PlaneActor_hpp

#include "Actor.hpp"

class PlaneActor : public Actor
{
public:
    PlaneActor(class Game* game);
    ~PlaneActor();
    class BoxComponent* GetBox() { return mBox; }
private:
    class BoxComponent* mBox;
};

#endif /* PlaneActor_hpp */
