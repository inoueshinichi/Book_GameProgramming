//
//  CameraComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include "Component.hpp"
#include "Math.hpp"

class CameraComponent : public Component
{
public:
    CameraComponent(class Actor* owner, int updateOrder = 200);
protected:
    void SetViewMatrix(const Matrix4& view);
};

#endif /* CameraComponent_hpp */
