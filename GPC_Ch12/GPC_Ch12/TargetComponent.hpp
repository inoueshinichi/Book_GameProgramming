//
//  TargetComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef TargetComponent_hpp
#define TargetComponent_hpp

#include "Component.hpp"

class TargetComponent : public Component
{
public:
    TargetComponent(class Actor* owner);
    ~TargetComponent();
};

#endif /* TargetComponent_hpp */
