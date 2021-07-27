R""(

#version 410 core

layout (location = 0) in float x;
layout (location = 1) in float y;
layout (location = 2) in float z;

uniform mat4 world2View;
uniform mat4 view2Clip;
uniform float pointSize;

void main()
{
    gl_Position = view2Clip * world2View * vec4(x, y, z, 1.0); // just choosing first the
    gl_PointSize = pointSize / gl_Position.w;
}

)""
