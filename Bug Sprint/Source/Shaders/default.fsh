#version 300 es

precision highp float;

in vec3 fColor;

out vec4 outColor;


void main(void)
{
    outColor = vec4(fColor, 1.0);
}
