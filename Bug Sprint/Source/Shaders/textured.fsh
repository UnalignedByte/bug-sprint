#version 300 es

precision highp float;

in vec4 fColor;
in vec2 fTexCoord;

uniform sampler2D diffuseSampler;

out vec4 outColor;


void main(void)
{
    outColor = texture(diffuseSampler, fTexCoord) * fColor;
}
