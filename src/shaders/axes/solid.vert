R""(

#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

out vec4 lineColor;

uniform mat4 world2View;
uniform mat4 view2Clip;

void main()
{
    gl_Position = view2Clip * world2View * vec4(pos, 1.0);
    lineColor = color;
}


)""
