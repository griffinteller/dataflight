R""(

#version 430 core

in vec2 texCoord;

uniform sampler2D buf0;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1, 1, 1, 1) - texture(buf0, texCoord);
}

)""