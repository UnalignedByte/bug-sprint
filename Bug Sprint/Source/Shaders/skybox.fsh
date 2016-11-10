#version 300 es

precision highp float;

in vec3 fTexCoord;

uniform samplerCube cubeSampler;

out vec4 outColor;


void main(void)
{
    outColor = texture(cubeSampler, fTexCoord);
}
