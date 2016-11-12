#version 300 es

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


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform Light light;
uniform Material material;

out vec3 fColor;


void main(void)
{
    vec3 color = vec3(0.0);

    // Ambient
    color += material.ambientIntensity * material.color * light.color;

    // Diffuse
    mat3 normalModelMatrix = mat3(modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz);
    vec3 transformedNormal = normalModelMatrix * normal;
    float diffuseIntensity = dot(transformedNormal, -light.direction) * material.diffuseIntensity;
    diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);
    color += diffuseIntensity * material.color * light.color;

    // Specular
    vec3 cameraDirection = normalize(viewMatrix[3].xyz - modelMatrix[3].xyz);
    vec3 lightDirectionReflected = normalize(reflect(light.direction, transformedNormal));
    float specularIntensity = dot(cameraDirection, lightDirectionReflected);
    if(specularIntensity > 0.0) {
        color += pow(specularIntensity, material.specularIntensity) * light.color;
    }

    fColor = color;

    // Position
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
