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

uint Shader::compileProgram(const char *vert, const char *frag, const char *geom)
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

    unsigned int geomShader;
    if (geom != nullptr)
    {
        geomShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geomShader, 1, &geom, nullptr);
        glCompileShader(geomShader);

        glGetShaderiv(geomShader, GL_COMPILE_STATUS, &compileSuccess);

        if (!compileSuccess)
        {
            char info[512];
            glGetShaderInfoLog(geomShader, 512, nullptr, info);
            std::cout << "GEOMETRY SHADER COMPILATION FAILURE:\n" << info << std::endl;
        }
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

    if (geom != nullptr)
        glAttachShader(program, geomShader);

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

    if (geom != nullptr)
        glDeleteShader(geomShader);

    return program;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometrySource)
{
    ID = compileProgram(vertexPath, fragmentPath, geometrySource);
}

void Shader::use() const
{
    glUseProgram(ID);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}
