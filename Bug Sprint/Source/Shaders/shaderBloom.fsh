#version 300 es

precision highp float;

in vec2 fTexCoord;

uniform sampler2D renderSampler;
uniform sampler2D bloomSampler;

out vec4 outColor;


void main()
{
    float weight[5];
    weight[0] = 0.227027;
    weight[1] = 0.1945946;
    weight[2] = 0.1216216;
    weight[3] = 0.054054;
    weight[4] = 0.016216;

    vec2 texelSize = 1.0 / vec2(textureSize(renderSampler, 0));

    vec3 blurred = texture(renderSampler, fTexCoord).rgb;

    vec3 b = texture(bloomSampler, fTexCoord).rgb;

    if(b.r > 0.0 || b.g > 0.0 || b.b > 0.0) {
        blurred *= weight[0];
        for(int i=1; i<10; i++) {
            blurred += texture(renderSampler, fTexCoord + vec2(texelSize.x * float(i/2), 0.0)).rgb * weight[i];
            blurred += texture(renderSampler, fTexCoord - vec2(texelSize.x * float(i/2), 0.0)).rgb * weight[i];
        }

        for(int i=1; i<10; i++) {
            blurred += texture(renderSampler, fTexCoord + vec2(0.0, texelSize.y * float(i/2))).rgb * weight[i];
            blurred += texture(renderSampler, fTexCoord - vec2(0.0, texelSize.y * float(i/2))).rgb * weight[i];
        }
    }

    outColor = /*texture(renderSampler, fTexCoord) +*/ vec4(blurred, 1.0);
}
