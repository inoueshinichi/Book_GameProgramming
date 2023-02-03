//
//  VertexArray.hpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

class VertexArray
{
public:
    VertexArray(const float* verts, unsigned int numVerts,
                const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();
    
    void SetActive();
    unsigned int GetNumIndices() const { return mNumIndices; }
    unsigned int GetNumVerts() const { return mNumVerts; }
private:
    // How many vertices in the vertex buffer?
    unsigned int mNumVerts;
    // How many indices in the index buffer?
    unsigned int mNumIndices;
    // OpenGL ID of the vertex buffer.
    unsigned int mVertexBuffer;
    // OpenGL ID of the index buffer.
    unsigned int mIndexBuffer;
    // OpenGL ID of the vertex array object.
    unsigned int mVertexArray;
};

#endif /* VertexArray_hpp */
