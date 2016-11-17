#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;

out vec3 fPosition;
out vec3 fNormal;
out vec4 fLightSpacePosition;


void main(void)
{
    fPosition = (viewMatrix * modelMatrix * vec4(position, 1.0)).xyz;

    fNormal = mat3(modelMatrix) * normal;

    fLightSpacePosition = lightProjectionMatrix * lightViewMatrix * modelMatrix * vec4(position, 1.0);

    // Positon
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
