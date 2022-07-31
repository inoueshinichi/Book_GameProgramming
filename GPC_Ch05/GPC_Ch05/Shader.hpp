//
//  Shader.hpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/30.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <string>
#include "Math.hpp"

class Shader
{
public:
    Shader();
    ~Shader();
    
    // 頂点シェーダ, フラグメントシェーダの読み込み
    bool Load(const std::string& vertName, const std::string& flagName);
    void Unload();
    
    void SetActive();
    
    void SetMatrixUniform(const char* name, const Matrix4& matrix);
    
private:
    // シェーダのコンパイル
    bool CompileShader(const std::string& fileName,
                       GLenum shaderType,
                       GLuint& outShader);
    // シェーダコンパイルが成功したかチェック
    bool IsCompiled(GLuint shader);
    
    // シェーダをリンクできたかチェック
    bool IsValidProgram();
    
private:
    // GLシェーダ ID
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;
};

#endif /* Shader_hpp */
