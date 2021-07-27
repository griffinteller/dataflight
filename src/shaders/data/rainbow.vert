R""(

#version 410 core

layout (location = 0) in float x;
layout (location = 1) in float y;
layout (location = 2) in float z;

uniform mat4 world2View;
uniform mat4 view2Clip;
uniform float pointSize;

out vec4 color;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    gl_Position = view2Clip * world2View * vec4(x, y, z, 1.0);
    gl_PointSize = pointSize / gl_Position.w;
    color = hsv2rgb(vec3(fract(gl_VertexID / 100.0), 1.0, 1.0)).xyzz;
}

)""
