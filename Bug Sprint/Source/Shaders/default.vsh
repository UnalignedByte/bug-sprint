#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightDirection;

flat out vec4 fColor;


void main(void)
{
    // Calculate light intensity
    mat3 normalModelMatrix = mat3(modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz);
    vec3 transformedNormal = normalModelMatrix * normal;
    float lightIntensity = dot(transformedNormal, lightDirection);

    // Color
    fColor = color * lightIntensity;

    // Position
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position.x, position.y, position.z, 1.0);
}
