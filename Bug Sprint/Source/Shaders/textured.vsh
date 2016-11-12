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
layout(location = 2) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform Light light;
uniform Material material;

out vec3 fColor;
out vec2 fTexCoord;


void main(void)
{
    // Calculate light intensity
    mat3 normalModelMatrix = mat3(modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz);
    vec3 transformedNormal = normalModelMatrix * normal;
    float diffuseIntensity = dot(transformedNormal, -light.direction) * material.diffuseIntensity;
    diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);

    // Color
    fColor = (material.ambientIntensity + diffuseIntensity) * material.color * light.color;

    // Texture
    fTexCoord = texCoord;

    // Position
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
