//
//  VertexArray.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/29.
//

#include "VertexArray.hpp"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts,
                         unsigned int numVerts,
                         const unsigned int* indices,
                         unsigned int numIndices)
    : mNumVerts(numVerts)
    , mNumIndices(numIndices)
{
    // 頂点配列オブジェクトの作成
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);
    
    // 頂点バッファの作成
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 numVerts * /*3*/ 5 * sizeof(float),
                 verts,
                 GL_STATIC_DRAW); // GPUでデータのロードを一回だけ行い, その後の描画で頻繁にデータを読み込む際に使う.
    
    // インデックスバッファの作成
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 numIndices * sizeof(unsigned int),
                 indices,
                 GL_STATIC_DRAW);
    
    // 頂点レイアウトを指定(float型の(x,y,z)で, オフセットを0とする)
    glEnableVertexAttribArray(0); // 最初の頂点属性を有効
    glVertexAttribPointer(0, // 属性インデックス(1つ目はゼロ)
                          3, // 要素数(ここでは3)
                          GL_FLOAT, // 要素の型
                          GL_FALSE, // (整数型のみ使用する)
                          sizeof(float) * 5 /*3*/, // ストライド(通常は各頂点のサイズ)
                          0 // 頂点データの開始位置からこの属性までのオフセット
                          );
    // ここまでで、頂点レイアウト(0)を設定した for (x,y,z) . (u,v)を追加する場合(x,y,z,u,v)
    // 頂点レイアウト(1)も設定する.glVertexAttribPointer(1, 2, ...)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, // 頂点属性インデックス
                          2, // 成分の数(UVは2個)
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 5, // ストライド(通常は各頂点のサイズ)
                          reinterpret_cast<void*>(sizeof(float) * 3) // オフセットポインタ
                          );
}


VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBuffer); // 頂点バッファ
    glDeleteBuffers(1, &mIndexBuffer);  // インデックスバッファ
    glDeleteVertexArrays(1, &mVertexArray); // 頂点配列オブジェクト
}

void VertexArray::SetActive()
{
    glBindVertexArray(mVertexArray);
}
