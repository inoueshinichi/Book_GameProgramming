//
//  Shader.cpp
//  GPC_Ch05
//
//  Created by Inoue Shinichi on 2022/06/30.
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
    // 頂点シェーダとフラグメントシェーダをコンパイルする
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
        !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }
    
    // 頂点 / フラグメントシェーダをリンクしてシェーダプログラムを作る
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);
    
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
    // この名前のuniformを探す
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    // 行列データをuniformに送る
    glUniformMatrix4fv(
                       loc, // Uniform ID
                       1,   // 行列の数(この場合は1個だけ)
                       GL_TRUE, // 行ベクトルを使うのならTRUE
                       matrix.GetAsFloatPtr() // 行列データへのポインタ
                       );
}

bool Shader::CompileShader(const std::string& fileName,
                           GLenum shaderType,
                           GLuint& outShader)
{
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open())
    {
        // ファイル内のすべてのテキストを文字列として読み込む
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();
        
        // シェーダタイプに応じたシェーダを作成
        outShader = glCreateShader(shaderType);
        
        // コンパイル
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
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
    
    // コンパイル状態の問い合わせ
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        return false;
    }
    
    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    
    // リンク状態の問い合わせ
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("GLSL Link Status:\n%s", buffer);
        return false;
    }
    
    return true;
}
