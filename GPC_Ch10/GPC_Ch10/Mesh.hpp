//
//  Mesh.hpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <string>
#include "Collision.hpp"

class Mesh final
{
public:
    Mesh();
    ~Mesh();
    
    bool Load(const std::string& fileName, class Renderer* renderer);
    void Unload();
    
    class VertexArray* GetVertexArray();
    class Texture* GetTexture(size_t index);
    
    const std::string GetShaderName() const { return mShaderName; }
    
    float GetRadius() const { return mRadius; }
    
    // Get object space bounding box
    const AABB& GetBox() const { return mBox; }
    
    float GetSpecPower() const { return mSpecPower; }
    
private:
    // AABB collision
    AABB mBox;
    
    std::vector<class Texture*> mTextures;
    
    class VertexArray* mVertexArray;
    
    std::string mShaderName;
    
    float mRadius;
    
    float mSpecPower;
};

#endif /* Mesh_hpp */
