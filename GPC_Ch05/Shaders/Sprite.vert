// Request GLSL 3.3
#version 330

// This should correspond to the data stored
// for each vertex in the vertex buffer.
// For now, just a position.
//in vec3 inPosition; // 頂点属性

// 属性0は位置, 属性1はテクスチャ座標
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

// フラグメントシェーダに伝えるテクスチャ座標
out vec2 fragTexCoord;

// ワールド変換とビュー射影のuniform変数
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;



void main()
{
    // The vertex shader needs to output a 4D coordinate.
    // For now set the 4th coordinate to 1.0
//    gl_Position = vec4(inPosition, 1.0);
    
    // 位置をワールド空間に、そしてクリップ空間に変換
    vec4 pos = vec4(inPosition, 1.0);
    gl_Position = pos * uWorldTransform * uViewProj;
    
    // テクスチャ座標をフラグメントシェーダにわたす
    fragTexCoord = inTexCoord;
}
