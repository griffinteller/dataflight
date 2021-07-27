R""(

#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

out vec4 lineColor;
out float lineCoord;  // even vertex is 0, odd is 1. Gets interpolated to coord

uniform mat4 world2View;
uniform mat4 view2Clip;

void main()
{
    gl_Position = view2Clip * world2View * vec4(pos, 1.0);
    lineColor = color;
    lineCoord = gl_VertexID % 2;
}


)""
