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
in vec3 fCameraPosition;
in vec3 fNormal;

uniform Light light;
uniform Material material;

out vec4 outColor;


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
    vec3 cameraDirection = normalize(fCameraPosition - fPosition);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, fNormal));
    float specularIntensity = dot(cameraDirection, lightDirectionReflected);
    if(specularIntensity > 0.0) {
        color += pow(specularIntensity, material.specularIntensity) * light.color;
    }

    outColor = vec4(color, 1.0);
}
