#version 300 es

precision highp float;

const int LightTypeDirectional = 1;
const int LightTypeSpotlight = 2;

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
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
uniform Light light0;
uniform Light light1;
uniform Material material;

uniform sampler2D shadowSampler;
uniform sampler2D diffuseSampler;

out vec4 outColor;


float directionalDiffuseIntensity(Light light)
{
    return dot(fNormal, -light.direction);
}


float spotlightDiffuseIntensity(Light light)
{
    vec3 fragmentDirection = normalize(fRawPosition - light.position);
    float theta = degrees(acos(dot(fragmentDirection, light.direction)));

    if(theta < light.cutOff) {
        return 1.0;
    }

    return 0.0;
}


float directionalSpecularIntensity(Light light)
{
    vec3 cameraDirection = normalize(eyePosition - fPosition);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, fNormal));
    return dot(cameraDirection, lightDirectionReflected);
}


float spotlightSpecularIntensity(Light light)
{
    return 0.0;
}


void main(void)
{
    vec3 color = vec3(0.0);

    // Diffuse


    // Light 0
    float diffuseIntensity0 = 0.0;
    if(light0.type == LightTypeDirectional)
        diffuseIntensity0 += directionalDiffuseIntensity(light0);
    else if(light0.type == LightTypeSpotlight)
        diffuseIntensity0 += spotlightDiffuseIntensity(light0);

    diffuseIntensity0 *= material.diffuseIntensity;
    diffuseIntensity0 = clamp(diffuseIntensity0, 0.0, 1.0);

    // Light 1
    float diffuseIntensity1 = 0.0;
    if(light1.type == LightTypeDirectional)
        diffuseIntensity1 += directionalDiffuseIntensity(light1);
    else if(light1.type == LightTypeSpotlight)
        diffuseIntensity1 += spotlightDiffuseIntensity(light1);

    diffuseIntensity1 *= material.diffuseIntensity;
    diffuseIntensity1 = clamp(diffuseIntensity1, 0.0, 1.0);

    // Specular
    float specularIntensity = 0.0;

    // Light 0
    if(light0.type == LightTypeDirectional)
        specularIntensity += directionalSpecularIntensity(light0);
    else if(light0.type == LightTypeSpotlight)
        specularIntensity += spotlightSpecularIntensity(light0);

    // Light 1
    /*if(light1.type == LightTypeDirectional)
        specularIntensity += directionalSpecularIntensity(light1);
    else if(light1.type == LightTypeSpotlight)
        specularIntensity += spotlightSpecularIntensity(light1);*/

    specularIntensity = max(specularIntensity, 0.0);

    // Shadow
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

    // Get Final Color
    vec3 diffuseColor = material.color;
    if(fTexCoord.x > 0.0 && fTexCoord.y > 0.0)
        diffuseColor *= vec3(texture(diffuseSampler, fTexCoord));

    color = material.ambientIntensity * diffuseColor * light0.color +
        /*(1.0 - shadowIntensity) */ (diffuseIntensity0 * diffuseColor * light0.color) +
        /*(1.0 - shadowIntensity) */ (pow(specularIntensity, material.specularIntensity) * light0.color);

    color += /*material.ambientIntensity * diffuseColor * light1.color +*/
    /*(1.0 - shadowIntensity) */ (diffuseIntensity1 * diffuseColor * light1.color) +
    /*(1.0 - shadowIntensity) */ (pow(specularIntensity, material.specularIntensity) * light1.color);

    outColor = vec4(color, 1.0);
}
