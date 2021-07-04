
R""(

#version 330 core

out vec4 fragColor;

in vec4 color;

void main()
{
    float armDist = floor(length(gl_PointCoord - vec2(0.5, 0.5)) * 2);

    if (armDist > 0.1)
        discard;

    fragColor = color;
}

)""
