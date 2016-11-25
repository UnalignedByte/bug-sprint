//
//  Drawable.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 21/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Instance.h"

#include <string>
#include <memory>
#include "Model.h"
#include "Texture.h"
#include "ShaderProgram.h"


class Drawable: public Instance
{
public:
    Drawable(const std::string &modelFileName, std::shared_ptr<ShaderProgram> shaderProgram);
    Drawable(const std::string &modelFileName, const std::string &textureFileName, std::shared_ptr<ShaderProgram> shaderProgram);
    Drawable(const std::string &modelFileName,
             const std::string &rightTextureFileName, const std::string &leftTextureFileName,
             const std::string &topTextureFileName, const std::string &bottomTextureFileName,
             const std::string &frontTextureFileName, const std::string backTextureFileName,
             std::shared_ptr<ShaderProgram> shaderProgram);

    std::shared_ptr<ShaderProgram> getShader() const;
    bool getShouldCastShadow() const;
    void setShouldCastShadow(bool shouldCastShadow);
    GLsizei getTrianglesCount() const override;

    void draw() override;
    void drawShadow(std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
    Model model;
    Texture texture;
    bool shouldCastShadow{true};
};

#endif
