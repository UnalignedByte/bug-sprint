#version 300 es

struct LightMatrix {
    mat4 viewMatrix;
    mat4 projectionMatrix;
};

layout(location = 0) in vec3 position;

uniform mat4 modelMatrix;
uniform int lightIndex;
uniform LightMatrix lightMatrices[8];


void main(void)
{
    gl_Position = lightMatrices[lightIndex].projectionMatrix * lightMatrices[lightIndex].viewMatrix * modelMatrix * vec4(position, 1.0);
}
