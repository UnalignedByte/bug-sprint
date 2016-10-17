#version 300 es


layout(location = 0) in vec4 position;
out vec4 fColor;


void main(void)
{
    gl_Position = position;
}
