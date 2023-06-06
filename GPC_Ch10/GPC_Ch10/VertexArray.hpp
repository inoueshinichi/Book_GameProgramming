//
//  VertexArray.hpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/03/11.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

class VertexArray final
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
    unsigned int mVertexBuffer;
    unsigned int mIndexBuffer;
    unsigned int mVertexArray;
};

#endif /* VertexArray_hpp */
