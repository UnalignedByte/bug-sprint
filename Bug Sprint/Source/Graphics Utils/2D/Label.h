//
// Created by Rafal Grodzinski on 20/11/2016.
//

#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <memory>
#include "Instance.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Color.h"


class Label: public Instance
{
public:
    Label(const std::string &text, const std::string &fontFileName, int fontSize, const Color &fontColor, std::shared_ptr<ShaderProgram> shaderProgram);

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
