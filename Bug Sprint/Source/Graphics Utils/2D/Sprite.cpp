//
// Created by Rafal Grodzinski on 18/11/2016.
//

#include "Sprite.h"

using namespace std;


struct Vertex {
    GLfloat position[2];
    GLfloat texCoords[2];
};


Sprite::Sprite(const std::string &spriteFileName,  shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), texture(spriteFileName), width(texture.getWidth()), height(texture.getHeight())
{
    Vertex vertices[6] = {{{-width/2.0f, -height/2.0f}, {0.0f, 1.0f}},
                          {{width/2.0f, height/2.0f}, {1.0f, 0.0f}},
                          {{-width/2.0f, height/2.0f}, {0.0f, 0.0f}},
                          {{-width/2.0f, -height/2.0f}, {0.0f, 1.0f}},
                          {{width/2.0f, -height/2.0f}, {1.0f, 1.0f}},
                          {{width/2.0f, height/2.0f}, {1.0f, 0.0f}}};

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}


shared_ptr<ShaderProgram> Sprite::getShader() const
{
    return shaderProgram;
}


GLint Sprite::getWidth() const
{
    return width;
}


GLint Sprite::getHeight() const
{
    return height;
}


void Sprite::draw()
{
    shaderProgram->use();
    texture.use(shaderProgram);

    GLint modelMatrixId = glGetUniformLocation(shaderProgram->getId(), "modelMatrix");
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, modelMatrix.getData());

    glBindVertexArray(vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
}

