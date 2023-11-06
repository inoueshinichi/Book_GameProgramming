//
//  VertexArray.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/04.
//

#include "VertexArray.hpp"
#include <GL/glew.h>

VertexArray::VertexArray(const void* verts,
                         unsigned numVerts,
                         Layout layout,
                         const unsigned* indices,
                         unsigned numIndices)
    : mNumVerts(numVerts)
    , mNumIndices(numIndices)
{
    // Create VA
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);
    
    unsigned vertexSize = 8 * sizeof(float);
    if (layout == PosNormSkinTex)
    {
        vertexSize += 8 * sizeof(char); // 8 * float<4> + 8 * char<1> = 40 bytes
    }
    
    // Create vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 numVerts * vertexSize,
                 verts,
                 GL_STATIC_DRAW);
    
    // Create index buffer
    glGenBuffers(1, &mIndiceBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndiceBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 numIndices * sizeof(unsigned),
                 indices,
                 GL_STATIC_DRAW);
    
    // specify the vertex attributes
    if (layout == PosNormTex)
    {
        // (x,y,z,nx,ny,nz,ux,vy)
        // 32 bytes
        
        // pos 3
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(/*attrib index in VA*/0,
                              /*属性の次元(x,y,z)*/3,
                              GL_FLOAT,
                              GL_FALSE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/0);
        
        // normal vec 3
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(/*attrib index in VA*/1,
                              /*属性の次元(nx,ny,nz)*/3,
                              GL_FLOAT,
                              GL_FALSE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/reinterpret_cast<void*>(sizeof(float) * 3));
                                  
        // texture coordinates 2
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(/*attrib index in VA*/2,
                              /*属性の次元(ux,vy)*/2,
                              GL_FLOAT,
                              GL_FALSE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/reinterpret_cast<void*>(sizeof(float) * 6));
        
    }
    else if (layout == PosNormSkinTex)
    {
        // (x,y,z,nx,ny,nz,sk1,sk2,sk3,sk4,skw1,skw2,skw3,skw4,ux,vy)
        // 40 bytes (32 + 8)
        
        // pos 3
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(/*attrib index in VA*/0,
                              /*属性の次元(x,y,z)*/3,
                              GL_FLOAT,
                              GL_FALSE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/0);
        
        // normal vec 3
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(/*attrib index in VA*/1,
                              /*属性の次元(nx,ny,nz)*/3,
                              GL_FLOAT,
                              GL_FALSE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/reinterpret_cast<void*>(sizeof(float) * 3));
                                  
        // skin indexs 4 (keep as ints)
        glEnableVertexAttribArray(2);
        glVertexAttribLPointer(/*attrib index in VA*/2,
                               /*属性の次元(sk1,sk2,sk3,sk4)*/4,
                               GL_UNSIGNED_BYTE,
                               /*1頂点のバイト数*/vertexSize,
                               /*オフセット*/reinterpret_cast<void*>(sizeof(float) * 6));
        
        // skin weights 4 (convert to floats)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(/*attrib index in VA*/3,
                              /*属性の次元(skw1,skw2,skw3,skw4)*/4,
                              GL_UNSIGNED_BYTE,
                              GL_TRUE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
        
        // texture coordinates (ux,vy)
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(/*attrib index in VA*/4,
                              /*属性の次元(ux,vy)*/2,
                              GL_FLOAT,
                              GL_FALSE,
                              /*1頂点のバイト数*/vertexSize,
                              /*オフセット*/reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
    }
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndiceBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
    glBindVertexArray(mVertexArray);
}
