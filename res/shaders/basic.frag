R""(

#version 430 core

out vec4 fragColor;

void main()
{
    float armDist = floor(length(gl_PointCoord - vec2(0.5, 0.5)) * 2);

    if (armDist > 0.1)
        discard;

    fragColor = vec4(1, 1, 1, 1.0);
}

)""
