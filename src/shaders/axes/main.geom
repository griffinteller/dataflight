R""(

#version 430 core

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT
{
    vec4 lineColor;
    float lineCoord;
} gs_in[];

out GS_OUT
{
    vec4 lineColor;
    float lineCoord;
} gs_out;

uniform float lineWidth;

void main()
{
    const float rad = lineWidth / 2;
    const vec4 lineDiff = gl_in[1].gl_Position - gl_in[0].gl_Position;
    const vec4 screenNorm = vec4(normalize(lineDiff.yx * vec2(1, -1)), 0, 0);

    //gl_Position = -screenNorm * rad * gl_in[0].gl_Position.w + gl_in[0].gl_Position;
    gl_Position = -screenNorm * rad + gl_in[0].gl_Position;
    gs_out.lineColor = gs_in[0].lineColor;
    gs_out.lineCoord = gs_in[0].lineCoord;
    EmitVertex();

    gl_Position = -screenNorm * rad + gl_in[1].gl_Position;
    gs_out.lineColor = gs_in[1].lineColor;
    gs_out.lineCoord = gs_in[1].lineCoord;
    EmitVertex();

    gl_Position = screenNorm * rad + gl_in[0].gl_Position;
    gs_out.lineColor = gs_in[0].lineColor;
    gs_out.lineCoord = gs_in[0].lineCoord;
    EmitVertex();

    gl_Position = screenNorm * rad + gl_in[1].gl_Position;
    gs_out.lineColor = gs_in[1].lineColor;
    gs_out.lineCoord = gs_in[1].lineCoord;
    EmitVertex();

    EndPrimitive();
}

)""
