#version 300 es

precision highp float;

in vec2 fTexCoord;

uniform sampler2D spriteSampler;

out vec4 outColor;


void main()
{
    vec4 color = texture(spriteSampler, fTexCoord);
    if(color.a < 0.1)
        discard;

    outColor= color;
}
