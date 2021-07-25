R""(

#version 430 core

in GS_OUT
{
    vec4 lineColor;
    float lineCoord;
} fs_in;

out vec4 fragColor;

uniform float dashLength; // proportion of total (ie 0 < dashLength < 1)

void main()
{
    if (int(floor(fs_in.lineCoord / dashLength)) % 2 == 1)
        discard;

    fragColor = fs_in.lineColor;
}

)""
