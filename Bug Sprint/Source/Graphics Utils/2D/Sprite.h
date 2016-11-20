//
// Created by Rafal Grodzinski on 18/11/2016.
//

#ifndef SPRITE_H
#define SPRITE_H

#include "Instance.h"

#include <memory>
#include "ShaderProgram.h"
#include "Texture.h"


class Sprite: public Instance
{
public:
    Sprite(const std::string &spriteFileName,  std::shared_ptr<ShaderProgram> shaderProgram);

    std::shared_ptr<ShaderProgram> getShader() const;
    GLint getWidth() const;
    GLint getHeight() const;

    void draw() override;

protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
    Texture texture;
    GLuint vertexArrayId;

    GLint width;
    GLint height;
};

#endif
