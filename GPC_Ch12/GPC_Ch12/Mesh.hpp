//
//  Mesh.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/03.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <string>
#include "Collision.hpp"

class Mesh
{
public:
    Mesh();
    ~Mesh();
    
    // load/unload mesh
    bool Load(const std::string& fileName, class Renderer* renderer);
    void Unload();
    // get the vertex array associated with this mesh
    class VertexArray* GetVertexArray() { return mVertexArray; }
    // get a texture from specified index
    class Texture* GetTexture(size_t index);
    
    const std::string& GetShaderName() const { return mShaderName; }
    
    // get object space bounding sphere radius
    float GetRadius() const { reutrn mRadius; }
    // get object space bounding box
    const AABB& GetBox() const { return mBox; }
    // get specular power of mesh
    float GetSpecPower() const { reutrn mSpecPower; }
    
private:
    // AABB collision
    AABB mBox;
    // Textures associated with this mesh
    std::vector<class Texture*> mTextures;
    // Vertex array associated with this mesh
    class VertexArray* mVertexArray;
    // Name of shader specified by mesh
    std::string mShaderName;
    // Stores object space bounding sphere radius
    float mRadius;
    // Specular power of surface
    float mSpecPower;
};

#endif /* Mesh_hpp */
