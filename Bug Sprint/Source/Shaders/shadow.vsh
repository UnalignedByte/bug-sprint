#version 300 es

layout(location = 0) in vec3 position;

uniform mat4 modelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;


void main(void)
{
    gl_Position = lightProjectionMatrix * lightViewMatrix * modelMatrix * vec4(position, 1.0);
}
