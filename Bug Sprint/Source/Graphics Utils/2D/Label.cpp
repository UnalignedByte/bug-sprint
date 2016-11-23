//
// Created by Rafal Grodzinski on 20/11/2016.
//

#include "Label.h"

#include "SystemUtils.h"

using namespace std;


struct Vertex {
    GLfloat position[2];
    GLfloat texCoords[2];
};


Label::Label(const std::string &text, const std::string &fontFileName, int fontSize, const Color &fontColor, std::shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), texture(text, fontFileName, fontSize, fontColor), width(texture.getWidth()), height(texture.getHeight())
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


shared_ptr<ShaderProgram> Label::getShader() const
{
    return shaderProgram;
}


GLint Label::getWidth() const
{
    return width;
}


GLint Label::getHeight() const
{
    return height;
}


void Label::draw()
{
    shaderProgram->use();
    texture.use(shaderProgram);

    GLint modelMatrixId = glGetUniformLocation(shaderProgram->getId(), "modelMatrix");
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, modelMatrix.getData());

    glBindVertexArray(vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
}
