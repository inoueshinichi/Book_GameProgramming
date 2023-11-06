//
//  TargetComponent.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#ifndef TargetComponent_hpp
#define TargetComponent_hpp

#include "Component.hpp"

class TargetComponent final : public Component
{
public:
    TargetComponent(class Actor* owner);
    ~TargetComponent();
};

#endif /* TargetComponent_hpp */
