//
//  MeshComponent.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
//

#ifndef MeshComponent_hpp
#define MeshComponent_hpp

#include "Component.hpp"
#include <cstddef>

class MeshComponent : public Component
{
public:
    MeshComponent(class Actor* owner, bool isSkeletal = false);
    ~MeshComponent();
    
    virtual void Draw(class Shader* shader);
    
    virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void SetTextureIndex(size_t index) { mTextureIndex = index; }
    
    void SetVisible(bool visible) { mVisible = visible; }
    bool GetVisible() const { return mVisible; }
    
    bool GetIsSkeletal() const { return mIsSkeletal; }
    
protected:
    class Mesh* mMesh;
    size_t mTextureIndex;
    bool mVisible;
    bool mIsSkeletal;
};

#endif /* MeshComponent_hpp */
