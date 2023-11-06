//
//  VertexArray.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/13.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

class VertexArray
{
public:
    VertexArray(const float* verts,
                unsigned int numVerts,
                const unsigned int* indices,
                unsigned int numIndices);
    ~VertexArray();
    
    void SetActive();
    unsigned int GetNumIndices() const { return mNumIndices; }
    unsigned int GetNumVerts() const { return mNumVerts; }
private:
    unsigned int mNumVerts;
    unsigned int mNumIndices;
    unsigned int mVertexBuffer; // OpenGL ID
    unsigned int mIndexBuffer; // OpenGL ID
    unsigned int mVertexArray;  // OpenGL ID
};

#endif /* VertexArray_hpp */
