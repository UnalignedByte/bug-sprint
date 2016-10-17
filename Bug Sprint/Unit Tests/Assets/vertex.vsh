#version 300 es


layout(location = 0) in vec4 position;
out vec4 fColor;


void main(void)
{
    fColor = vec4(1.0);
    gl_Position = position;
}
