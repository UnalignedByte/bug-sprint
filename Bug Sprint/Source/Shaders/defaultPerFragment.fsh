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

uniform vec3 eyePosition;
uniform Light light;
uniform Material material;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec4 bloomColor;


void main(void)
{
    vec3 color = vec3(0.0);

    // Ambient
    color += material.ambientIntensity * material.color * light.color;

    // Diffuse
    float diffuseIntensity = dot(fNormal, -light.direction) * material.diffuseIntensity;
    diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);
    color += diffuseIntensity * material.color * light.color;

    // Specular
    vec3 cameraDirection = normalize(eyePosition - fPosition);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, fNormal));
    float specularIntensity = dot(cameraDirection, lightDirectionReflected);
    if(specularIntensity > 0.0) {
        color += pow(specularIntensity, material.specularIntensity) * light.color;
    }

    outColor = vec4(color, 1.0);
    //float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    /*if(brightness > 1.0)
        bloomColor = vec4(color, 1.0);*/
}
