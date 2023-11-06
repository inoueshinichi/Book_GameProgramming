//
//  Shader.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
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
    bool Load(const std::string& vertName, const std::string& fragName);
    void Unload();
    void SetActive();
    void SetMatrixUniform(const char* name, const Matrix4& matrix);
    void SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned int count);
    void SetVectorUniform(const char* name, const Vector3& vector);
    void SetFloatUniform(const char* name, float value);
    
private:
    bool CompileShader(cosnt std::string& fileName,
                       GLenum shaderType,
                       GLuint& outShader);
    
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();
    
private:
    // store the shader object IDs
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;
};

#endif /* Shader_hpp */
