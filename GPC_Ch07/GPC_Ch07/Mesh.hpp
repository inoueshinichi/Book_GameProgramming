//
//  Mesh.hpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/20.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <string>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    
    // Load/unload mesh
    bool Load(const std::string& fileName, class Renderer* renderer);
    void Unload();
    
    // Get the vertex array associated with this mesh
    class VertexArray* GetVertexArray() { return mVertexArray; }
    
    // Get a texture from specified index
    class Texture* GetTexture(size_t index);
    
    // Get name of shader
    const std::string& GetShaderName() const { return mShaderName; }
    
    // Get object space bounding sphere radius
    float GetRadius() const { return mRadius; }
    
    // Get specular power of mesh
    float GetSpecPower() const { return mSpecPower; }
private:
    // Textures associated with this mesh
    std::vector<class Texture*> mTextures;
    // Vertex array associated this mesh
    class VertexArray* mVertexArray;
    // Name of shader specified by mesh
    std::string mShaderName;
    // Stores object space bounding sphere radius
    float mRadius;
    // Specular power of surface
    float mSpecPower;
};

#endif /* Mesh_hpp */
