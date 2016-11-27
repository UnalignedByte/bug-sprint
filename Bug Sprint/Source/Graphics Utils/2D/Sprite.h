//
// Created by Rafal Grodzinski on 18/11/2016.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "Instance2D.h"

#include <memory>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Color.h"


class Sprite: public Instance2D
{
public:
    Sprite(const std::string &imageFileName,  std::shared_ptr<ShaderProgram> shaderProgram);
    Sprite(const std::string &text, const std::string &fontFileName, GLfloat fontSize, const Color &fontColor, std::shared_ptr<ShaderProgram> shaderProgram);

    virtual std::shared_ptr<ShaderProgram> getShader() const;
    virtual GLfloat getWidth() const;
    virtual GLfloat getHeight() const;

    void draw() override;

protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
    Texture texture;
    GLuint vertexArrayId;

    GLfloat width;
    GLfloat height;

protected:
    void setupVertexArray();
};

#endif
