#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fPosition;
out vec3 fCameraPosition;
out vec3 fNormal;


void main(void)
{
    fPosition = (viewMatrix * modelMatrix * vec4(position, 1.0)).xyz;

    fCameraPosition = viewMatrix[3].xyz;

    fNormal = mat3(modelMatrix) * normal;

    // Positon
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
