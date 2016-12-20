#version 300 es

precision highp float;

const int LightTypeUnused = 0;
const int LightTypeDirectional = 1;
const int LightTypeSpot = 2;
const int LightTypePoint = 3;

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
    float cutOff;
    float innerCutOff;
};

struct Material {
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};


in vec3 fPosition;
in vec3 fNormal;
in vec4 fLightSpacePosition;
in vec2 fTexCoord;
in mat4 fModelViewMatrix;
in vec3 fRawPosition;

uniform vec3 eyePosition;
uniform Light lights[8];
uniform Material material;

uniform sampler2D shadowSampler;
uniform sampler2D diffuseSampler;

out vec4 outColor;


vec3 directionalLightColor(Light light, float shadowIntensity)
{
    vec3 diffuseColor = material.color;
    if(fTexCoord.x > 0.0 && fTexCoord.y > 0.0)
        diffuseColor *= vec3(texture(diffuseSampler, fTexCoord));

    // Diffuse intensity
    float diffuseIntensity = dot(fNormal, -light.direction) * light.diffuseIntensity;
    diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);

    // Specular intensity
    vec3 cameraDirection = normalize(eyePosition - fPosition);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, fNormal));
    float specularIntensity = dot(cameraDirection, lightDirectionReflected) * light.specularIntensity;
    specularIntensity = clamp(specularIntensity, 0.0, 1.0);

    vec3 color = material.ambientIntensity * diffuseColor * light.color * light.ambientIntensity +
                 (1.0 - shadowIntensity) * (diffuseIntensity * diffuseColor * light.color) +
                 (1.0 - shadowIntensity) * (pow(specularIntensity, material.specularIntensity) * light.color);

    return color;
}


vec3 spotLightColor(Light light, float shadowIntensity)
{
    vec3 diffuseColor = material.color;
    if(fTexCoord.x > 0.0 && fTexCoord.y > 0.0)
        diffuseColor *= vec3(texture(diffuseSampler, fTexCoord));

    // Diffuse intensity
    vec3 fragmentDirection = normalize(fRawPosition - light.position);
    float theta = degrees(acos(dot(fragmentDirection, light.direction)));
    float epsilon = light.innerCutOff - light.cutOff - 0.01;
    float diffuseIntensity = clamp((theta - light.cutOff)/epsilon, 0.0, 1.0) * light.diffuseIntensity;

    vec3 color = material.ambientIntensity * diffuseColor * light.color * light.ambientIntensity +
                 (1.0 - shadowIntensity) * (diffuseIntensity * diffuseColor * light.color);

    return color;
}


vec3 pointLightColor(Light light, float shadowIntensity)
{
    return vec3(0.0);
}


void main(void)
{
    // Calculate shadow intensity
    float shadowIntensity = 0.0;

    vec3 lightNdcPosition = fLightSpacePosition.xyz / fLightSpacePosition.w;
    vec2 lightTexCoord = vec2(lightNdcPosition.x * 0.5 + 0.5, lightNdcPosition.y * 0.5 + 0.5);
    if(lightTexCoord.x >= 0.0 && lightTexCoord.x <= 1.0 && lightTexCoord.y >= 0.0 && lightTexCoord.y <= 1.0) {
        float lightZ = lightNdcPosition.z * 0.5 + 0.5;

        vec2 shadowTexSize = vec2(textureSize(shadowSampler, 0));
        for(int y=-1; y<=1; y++) {
            for(int x=-1; x<=1; x++) {
                float shadowTexZ = texture(shadowSampler, lightTexCoord + vec2(x,y) / shadowTexSize).x;
                if(lightZ - 0.005 > shadowTexZ)
                    shadowIntensity += 1.0;
            }
        }

        shadowIntensity *= 0.75 / 9.0;
    }

    // Calculate Final Color
    vec3 color = vec3(0.0);

    for(int i=0; i<8; i++) {
        if(lights[i].type == LightTypeDirectional) {
            color += directionalLightColor(lights[i], shadowIntensity);
        } else if(lights[i].type == LightTypeSpot) {
            color += spotLightColor(lights[i], shadowIntensity);
        } else if(lights[i].type == LightTypePoint) {
            color += pointLightColor(lights[i], shadowIntensity);
        }
    }

    outColor = vec4(color, 1.0);
}
