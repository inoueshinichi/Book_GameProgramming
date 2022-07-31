//
//  CircleComponent.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/14.
//

#ifndef CircleComponent_hpp
#define CircleComponent_hpp

#include "Component.hpp"
#include "Math.hpp"

class CircleComponent : public Component
{
public:
    CircleComponent(class Actor* owner);
    
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const;
    
    const Vector3& GetCenter() const;
private:
    float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);

#endif /* CircleComponent_hpp */
