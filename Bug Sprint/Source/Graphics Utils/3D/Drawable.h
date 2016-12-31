//
//  Drawable.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 21/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Instance3D.h"

#include <string>
#include <memory>
#include "Model.h"
#include "Texture.h"
#include "ShaderProgram.h"


class Drawable: public Instance3D
{
public:
    Drawable(const std::string &modelFileName);
    Drawable(const std::string &modelFileName, const std::string &textureFileName);
    Drawable(const std::string &modelFileName,
             const std::string &rightTextureFileName, const std::string &leftTextureFileName,
             const std::string &topTextureFileName, const std::string &bottomTextureFileName,
             const std::string &frontTextureFileName, const std::string backTextureFileName);

    GLsizei getTrianglesCount() const override;

    virtual Model &getModel();
    virtual Texture &getTexture();

    void draw(std::shared_ptr<ShaderProgram> shaderProgram) override;

protected:
    Model model;
    Texture texture;
    bool shouldCastShadow{true};
    bool isShaded{true};
};

#endif
