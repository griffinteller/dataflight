R""(

#version 430 core

in GS_OUT
{
    vec4 lineColor;
    float lineCoord;
} fs_in;

out vec4 fragColor;

void main()
{
    fragColor = fs_in.lineColor;
}

)""
