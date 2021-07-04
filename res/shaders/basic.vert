R""(

#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 world2View;
uniform mat4 view2Clip;
uniform float pointSize;

void main()
{
    gl_Position = view2Clip * world2View * vec4(pos, 1.0);
    gl_PointSize = pointSize / gl_Position.w;
}

)""
