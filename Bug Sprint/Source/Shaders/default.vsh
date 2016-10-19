#version 300 es

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

flat out vec4 fColor;


void main(void)
{
    fColor = color;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position.x, position.y, position.z, 1.0);
}
