//
//  Shader.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/13.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <string>
#include "Math.hpp"
#include "Game.hpp" // ASSETS_DIR

class Shader
{
public:
    Shader();
    ~Shader();
    
    // Load the vertex/fragment shaders with the given names
    bool Load(const std::string& vertName,
              const std::string& fragName);
    
    void Unload();
    
    // Set this as the active shader program
    void SetActive();
    
    // Sets a Matrix uniform
    void SetMatrixUniform(const char* name,
                          const Matrix4& matrix);
    
    // Set a Vector3 uniform
    void SetVectorUniform(const char* name,
                          const Vector3& vector);
    
    // Set a float uniform
    void SetFloatUniform(const char* name,
                         float value);
    
private:
    // Tries to compile the specified shader
    bool CompileShader(const std::string& fileName,
                       GLenum shaderType,
                       GLuint& outShader);
    
    // Test whether shader compiled successfully
    bool IsCompiled(GLuint shader);
    
    // Tests whether vertex/fragment programs link
    bool IsValidProgram();
    
private:
    // Store the shader object IDs
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;
};

#endif /* Shader_hpp */
