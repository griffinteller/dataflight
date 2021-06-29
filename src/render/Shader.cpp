//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>
#include <iostream>
#include "Shader.h"

uint Shader::getID() const
{
    return ID;
}

uint Shader::compileProgram(const char *vert, const char *frag)
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vert, nullptr);
    glCompileShader(vertexShader);

    int compileSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileSuccess);

    if (!compileSuccess)
    {
        char info[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cout << "VERTEX SHADER COMPILATION FAILURE:\n" << info << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess)
    {
        char info[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cout << "FRAGMENT SHADER COMPILATION FAILURE:\n" << info << std::endl;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetShaderiv(program, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess)
    {
        char info[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cout << "SHADER PROGRAM COMPILATION FAILURE:\n" << info << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

Shader::Shader(const char *vertexSource, const char *fragmentSource)
{
    ID = compileProgram(vertexSource, fragmentSource);
}

void Shader::use() const
{
    glUseProgram(ID);
}
