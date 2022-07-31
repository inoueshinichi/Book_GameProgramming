// GLSL 3.3
#version 330

// カラーバッファへの出力色
out vec4 outColor;

// テクスチャ座標
in vec2 fragTexCoord;

// テクスチャサンプラー用
uniform sampler2D uTexture;

void main()
{
    // 出力色を青に設定する
    //outColor = vec4(0.0, 0.0, 1.0, 1.0);
    
    // テクスチャから色をサンプリングする
    outColor = texture(uTexture, fragTexCoord);
}
