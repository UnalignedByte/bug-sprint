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
#include "Light.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"


class Drawable: public Instance3D
{
public:
    Drawable();
    Drawable(const std::string &modelFileName);
    Drawable(const std::string &modelFileName, const std::string &textureFileName);
    Drawable(const std::string &modelFileName,
             const std::string &rightTextureFileName, const std::string &leftTextureFileName,
             const std::string &topTextureFileName, const std::string &bottomTextureFileName,
             const std::string &frontTextureFileName, const std::string backTextureFileName);

    GLsizei getTrianglesCount() const override;

    virtual bool getShouldCastShadow(std::shared_ptr<Light> light) const;
    virtual void setShouldCastShadow(bool shouldCastShadow);

    virtual std::shared_ptr<Model> getModel() const;
    virtual std::shared_ptr<Texture> getTexture() const;

    virtual void draw(std::shared_ptr<ShaderProgram> shaderProgram);
    virtual void drawShadow(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Light> light);

protected:
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> texture;
    bool shouldCastShadow{true};
};

#endif
