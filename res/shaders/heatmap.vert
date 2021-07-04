R""(

#version 330 core

layout (location = 0) in vec3 pos;

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
    gl_Position = view2Clip * world2View * vec4(pos, 1.0);
    gl_PointSize = pointSize / gl_Position.w;
    color = vec4(gl_Position.xyz + vec3(0.5, 0.5, 0.5), 1.0);
}

)""
