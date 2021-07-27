R""(

#version 410 core

layout (location = 0) in vec2 pos;

out vec2 texCoord;

void main()
{
    // transforms 0-1 coords to -1,1, which is what gl_Position expects
    gl_Position = vec4(pos * 2 - vec2(1, 1), 0, 1.0);
    texCoord = pos;
}

)""