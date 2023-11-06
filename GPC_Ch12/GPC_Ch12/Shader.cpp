//
//  Shader.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/02.
//

#include "Shader.hpp"
#include "Texture.hpp"
#include <SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader()
    : mShaderProgram(0)
    , mVertexShader(0)
    , mFragShader(0)
{}

Shader::~Shader()
{}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    // compile
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
        !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }
    
    // link
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);
    
    // 検証
    if (!IsValidProgram())
    {
        return false;
    }
    
    return true;
}


void Shader::Unload()
{
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
    glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetMatrixUniforms(const char* name,
                               Matrix4* matrices, unsigned int count)
{
    GLuint loc = glGetUniformLocaiton(mShaderProgram, name)
    glUniformMatrix4(loc, count, GL_TRUE, matrices->GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char *name, float value)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniform1f(loc, value);
}

bool Shader::CompileShader(const std::string& fileName,
                           GLenum shaderType,
                           GLuint& outShader)
{
    // Open file
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open())
    {
        // read all of the text into a string
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        
        std::string contents = sstream.str();
        const char* contentChar = contents.c_str();
        
        // create a shader of the specified type
        outShader = glCreateShader(shaderType);
        
        // set the source characters and try to compile
        glShaderSource(outShader, 1, &(contentChar), nullptr)
        glCompileShader(outShader);
        
        if (!IsCompiled(outShader))
        {
            SDL_Log("Failed to compile shader %s", fileName.c_str());
                        return false;
        }
    }
    else
    {
        SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }
    
    return true;
}


bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    // query the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status != GL_TRUE)
    {
        char buffer[512];
        std::memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        return false;
    }
    
    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    // query the lin status
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        std::memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("GLSL Link Status:\n%s", buffer);
        return false;
    }
    return true;
}
