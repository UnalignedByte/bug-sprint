#version 300 es

precision highp float;
precision highp sampler2DArray;

in vec2 fTexCoord;

uniform sampler2DArray diffuseSampler;

out vec4 outColor;


void main()
{
    float depth = texture(diffuseSampler, vec3(fTexCoord, 1)).x;
    //if(color.a < 0.1)
    //    discard;

    outColor = vec4(depth, depth, depth, 1.0);
    //outColor = vec4(1.0, 0.0, 0.0, 1.0);
    //outColor = texture(diffuseSampler, vec3(fTexCoord, 0));
}
