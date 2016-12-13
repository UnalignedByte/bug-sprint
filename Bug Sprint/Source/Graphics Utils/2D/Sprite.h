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
    Sprite(const std::string &imageFileName);
    Sprite(const std::string &text, const std::string &fontFileName, GLfloat fontSize, const Color &fontColor);

    void draw(std::shared_ptr<ShaderProgram> shaderProgram) override;

protected:
    Texture texture;
    GLuint vertexArrayId;

protected:
    void setupVertexArray();
};

#endif
