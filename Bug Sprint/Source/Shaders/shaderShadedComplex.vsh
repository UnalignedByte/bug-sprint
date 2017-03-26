#version 300 es

struct LightMatrix {
    mat4 viewMatrix;
    mat4 projectionMatrix;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform LightMatrix lightMatrices[8];

out vec3 fPosition;
out vec3 fNormal;
out vec4 fLightSpacePosition[8];
out vec2 fTexCoord;
out mat4 fModelViewMatrix;
out vec3 fRawPosition;


void main(void)
{
    fModelViewMatrix = viewMatrix * modelMatrix;
    fPosition = (viewMatrix * modelMatrix * vec4(position, 1.0)).xyz;
    fRawPosition = (modelMatrix * vec4(position, 1.0)).xyz;

    fNormal = mat3(modelMatrix) * normal;

    for(int i=0; i<8; i++) {
        fLightSpacePosition[i] = lightMatrices[i].projectionMatrix * lightMatrices[i].viewMatrix * modelMatrix * vec4(position, 1.0);
    }

    fTexCoord = texCoord;

    // Positon
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
