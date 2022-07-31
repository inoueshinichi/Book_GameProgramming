//
//  MeshComponent.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/15.
//

#ifndef MeshComponent_hpp
#define MeshComponent_hpp

#include "Component.hpp"
#include <cstddef>

class MeshComponent : public Component
{
public:
    MeshComponent(class Actor* owner);
    ~MeshComponent();
    
    // Draw this mesh component
    virtual void Draw(class Shader* shader);
    
    // Set the mesh/texture index used by mesh component
    virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    
    void SetTextureIndex(size_t index) { mTextureIndex = index; }
protected:
    class Mesh* mMesh;
    size_t mTextureIndex;
};

#endif /* MeshComponent_hpp */
