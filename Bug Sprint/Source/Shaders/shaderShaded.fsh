#version 300 es

precision highp float;
precision highp sampler2D;

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


in mat4 fModelViewMatrix;
in vec3 fPosition;
in vec3 fRawPosition;
in vec3 fNormal;
in vec4 fLightSpacePosition;
in vec2 fTexCoord;

uniform vec3 eyePosition;
uniform Light lights[8];
uniform Material material;

uniform sampler2D diffuseSampler;
uniform sampler2D shadowSampler;

layout (location = 1) out vec4 bloomColor;
layout (location = 0) out vec4 outColor;


vec3 directionalLightColor(Light light, float shadowIntensity)
{
    vec3 diffuseColor = material.color;
    if(fTexCoord.x > 0.0 && fTexCoord.y > 0.0)
        diffuseColor *= vec3(texture(diffuseSampler, fTexCoord));

    // Diffuse intensity
    float diffuseIntensity = dot(fNormal, -light.direction) * light.diffuseIntensity;
    diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);

    // Specular intensity
    // Phong
    /*vec3 cameraDirection = normalize(eyePosition - fPosition);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, fNormal));
    float specularIntensity = dot(cameraDirection, lightDirectionReflected) * light.specularIntensity;*/

    // Blinn-Phong
    vec3 cameraDirection = normalize(eyePosition - fPosition);
    vec3 halfwayDirection = normalize(cameraDirection - light.direction);
    float specularIntensity = dot(fNormal, halfwayDirection);

    specularIntensity = max(specularIntensity, 0.0);

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
    float diffuseIntensity = 0.0;
    bool isFragmentInLight = dot(fNormal, normalize(-light.direction)) >= 0.0;
    if(isFragmentInLight) {
        vec3 fragmentDirection = normalize(light.position - fRawPosition);
        float theta = dot(fragmentDirection, normalize(-light.direction));
        theta = degrees(acos(theta));

        float epsilon = light.innerCutOff - light.cutOff - 0.01;
        diffuseIntensity = (theta - light.cutOff)/epsilon;
        diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);

        float dist = length(light.position - fRawPosition);
        float attenuation = 1.0 / (1.0 + 0.01 * dist + 0.005 * dist * dist);
        diffuseIntensity = diffuseIntensity * attenuation;
    }

    vec3 color = material.ambientIntensity * diffuseColor * light.color * light.ambientIntensity +
                 (1.0 - (shadowIntensity - diffuseIntensity)) * (diffuseIntensity * diffuseColor * light.color);

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
    float shadowIterations = 0.0;

    vec3 lightNdcPosition = fLightSpacePosition.xyz / fLightSpacePosition.w;
    vec2 lightTexCoord = vec2(lightNdcPosition.x * 0.5 + 0.5, lightNdcPosition.y * 0.5 + 0.5);
    if(lightNdcPosition.z >= -1.0 && lightNdcPosition.z <= 1.0 && lightTexCoord.x >= 0.0 && lightTexCoord.x <= 1.0 && lightTexCoord.y >= 0.0 && lightTexCoord.y <= 1.0) {
        float lightZ = lightNdcPosition.z * 0.5 + 0.5;

        //float shadowTexZ = texture(shadowSampler, vec2(lightTexCoord.x, lightTexCoord.y)).x;
        //if(lightZ - 0.005 > shadowTexZ) {
        //    shadowIntensity = 0.75;
        //}

        vec2 shadowTexSize = vec2(textureSize(shadowSampler, 0));
        for(int y=-1; y<=1; y++) {
            for(int x=-1; x<=1; x++) {
                shadowIterations += 1.0;
                float shadowTexZ = texture(shadowSampler, vec2(lightTexCoord + vec2(x,y) / shadowTexSize)).x;
                if(lightZ - 0.005 > shadowTexZ)
                    shadowIntensity += 1.0;
            }
        }

    }

    shadowIntensity *= 0.75 / shadowIterations;

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
    float grey = (color.r + color.g + color.b) / 3.0;
    if(grey > 0.5)
        bloomColor = vec4(color, 1.0);
    else
        bloomColor = vec4(0.0, 0.0, 0.0, 1.0);
    /*float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
     bloomColor = vec4(color, 1.0);
    else
        bloomColor = vec4(0.0, 0.0, 0.0, 1.0);*/
}
