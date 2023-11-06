//
//  VertexArray.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/04.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

class VertexArray
{
public:
    
    // Different supported vertex layouts
    enum Layout
    {
        PosNormTex,
        PosNormSkinTex
    };
    
    VertexArray(const void* verts, unsigned numVerts, Layout layout,
                const unsigned* indices, unsigned numIndices);
    ~VertexArray();
    
    void SetActive();
    unsigned GetNumIndices() const { return mNumIndices; }
    unsigned GetNumVerts() const { return mNumVerts; }
    
private:
    // 頂点バッファ数
    unsigned mNumVerts;
    // インデックスバッファ数
    unsigned mNumIndices;
    // OpenGL 頂点バッファID
    unsigned mVertexBuffer;
    // OpenGL インデックスバッファID
    unsigned mIndiceBuffer;
    // OpenGL VAID
    unsigned mVertexArray;
};

#endif /* VertexArray_hpp */
