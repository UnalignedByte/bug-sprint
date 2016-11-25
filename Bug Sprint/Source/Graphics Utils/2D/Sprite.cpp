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
    setupVertexArray();
}


Sprite::Sprite(const std::string &text, const std::string &fontFileName, GLfloat fontSize, const Color &fontColor, std::shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), texture(text, fontFileName, fontSize, fontColor), width(texture.getWidth()), height(texture.getHeight())
{
    setupVertexArray();
}


void Sprite::setupVertexArray()
{
    GLfloat halfWidth = width/2.0;
    GLfloat halfHeight = height/2.0;

    Vertex vertices[6] = {{{-halfWidth, -halfHeight}, {0.0f, 1.0f}},
                          {{+halfWidth, +halfHeight}, {1.0f, 0.0f}},
                          {{-halfWidth, +halfHeight}, {0.0f, 0.0f}},
                          {{-halfWidth, -halfHeight}, {0.0f, 1.0f}},
                          {{+halfWidth, -halfHeight}, {1.0f, 1.0f}},
                          {{+halfWidth, +halfHeight}, {1.0f, 0.0f}}};

    trianglesCount = sizeof(vertices)/sizeof(Vertex);

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    shaderProgram->use();
    texture.use(shaderProgram);

    GLint modelMatrixId = glGetUniformLocation(shaderProgram->getId(), "modelMatrix");
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, modelMatrix.getData());

    glBindVertexArray(vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

    glDisable(GL_BLEND);
}

