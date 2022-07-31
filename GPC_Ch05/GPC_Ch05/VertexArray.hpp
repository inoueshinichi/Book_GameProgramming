//
//  VertexArray.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

class VertexArray
{
public:
    VertexArray(const float* verts, // 頂点バッファ配列
                unsigned int numVerts, // 頂点バッファ数
                const unsigned int* indices, // インデックスバッファ配列
                unsigned int numIndices); // インデックスバッファ数
    ~VertexArray();
    
    // この頂点配列をアクティブにする(描画できるようにする)
    void SetActive();
    
    unsigned int GetNumIndices() const { return mNumIndices; }
    unsigned int GetNumVerts() const { return mNumVerts; }
    
private:
    unsigned int mNumVerts;     // 頂点バッファにある頂点の数
    unsigned int mNumIndices;   // インデックスバッファにあるインデックスの数
    unsigned int mVertexBuffer; // 頂点バッファのOpenGL ID
    unsigned int mIndexBuffer;  // インデックスバッファのOpenGL ID
    unsigned int mVertexArray;  // 頂点配列オブジェクトのOpenGL ID
};

#endif /* VertexArray_hpp */
