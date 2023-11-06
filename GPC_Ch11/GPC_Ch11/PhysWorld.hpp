//
//  PhysWorld.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#ifndef PhysWorld_hpp
#define PhysWorld_hpp

#include <vector>
#include <functional>
#include "Math.hpp"
#include "Collision.hpp"

class PhysWorld
{
public:
    PhysWorld(class Game* game);
    
    // Used to give helpful information about collision results
    struct CollisionInfo
    {
        // Point of collision
        Vector3 mPoint;
        // Normal at collision
        Vector3 mNormal;
        // Component collied with
        class BoxComponent* mBox;
        // Owning actor of component
        class Actor* mActor;
    };
    
    // Test a line segment against boxes
    // Returns true if it collieds against a box
    bool SegmentCast(const LineSegment& l, CollisionInfo& outColl);
    
    // Tests collisions using naive pairwise
    void TestPairwise(std::function<void(class Actor*, class Actor*)> f);
    
    // Test collisions using sweep and prune
    void TestSweepAndPrune(std::function<void(class Actor*, class Actor*)> f);
    
    // Add/remove box components from world
    void AddBox(class BoxComponent* box);
    void RemoveBox(class BoxComponent* box);
    
private:
    class Game* mGame;
    std::vector<class BoxComponent*> mBoxes;
};

#endif /* PhysWorld_hpp */
