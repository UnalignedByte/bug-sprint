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
layout(location = 3) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform Material material;

out vec3 fTexCoord;


void main(void)
{
    fTexCoord = position;

    mat4 modifiedViewMatrix = viewMatrix;
    modifiedViewMatrix[3][0] = 0.0;
    modifiedViewMatrix[3][1] = 0.0;
    modifiedViewMatrix[3][2] = 0.0;

    // Multiply the skybox by 1000
    mat4 scaleMatrix = mat4(
    1000.0, 0.0, 0.0, 0.0,
    0.0, 1000.0, 0.0, 0.0,
    0.0, 0.0, 1000.0, 0.0,
    0.0, 0.0, 0.0, 1.0
    );

    vec4 modifiedPosition = projectionMatrix * scaleMatrix * modifiedViewMatrix * vec4(position.x, position.y, position.z, 1.0);

    gl_Position = modifiedPosition.xyww;
}
