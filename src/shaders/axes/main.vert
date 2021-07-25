R""(

#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

out VS_OUT {
    vec4 lineColor;
    float lineCoord;// even vertex is 0, odd is 1. Gets interpolated to coord
} vs_out;

uniform mat4 world2View;
uniform mat4 view2Clip;

void main()
{
    gl_Position = view2Clip * world2View * vec4(pos, 1.0);
    vs_out.lineColor = color;
    vs_out.lineCoord = gl_VertexID % 2;
}


)""
