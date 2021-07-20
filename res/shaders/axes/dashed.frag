R""(

#version 430 core

in vec4 lineColor;
in float lineCoord;

out vec4 fragColor;

uniform float dashLength; // proportion of total (ie 0 < dashLength < 1)

void main()
{
    if (int(floor(lineCoord / dashLength)) % 2 == 1)
        discard;

    fragColor = lineColor;
}

)""
