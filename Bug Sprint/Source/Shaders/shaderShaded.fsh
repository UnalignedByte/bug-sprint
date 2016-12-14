#version 300 es

precision highp float;

struct Light {
    vec3 direction;
    vec3 color;
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

uniform vec3 eyePosition;
uniform Light light;
uniform Material material;

uniform sampler2D shadowSampler;
uniform sampler2D diffuseSampler;

out vec4 outColor;


void main(void)
{
    vec3 color = vec3(0.0);

    // Diffuse
    float diffuseIntensity = dot(fNormal, -light.direction) * material.diffuseIntensity;
    diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);

    // Specular
    vec3 cameraDirection = normalize(eyePosition - fPosition);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, fNormal));
    float specularIntensity = dot(cameraDirection, lightDirectionReflected);
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
    vec3 diffuseColor = material.color * vec3(texture(diffuseSampler, fTexCoord));
    color = material.ambientIntensity * diffuseColor * light.color +
        (1.0 - shadowIntensity) * (diffuseIntensity * diffuseColor * light.color) +
        (1.0 - shadowIntensity) * (pow(specularIntensity, material.specularIntensity) * light.color);

    outColor = vec4(color, 1.0);
}
