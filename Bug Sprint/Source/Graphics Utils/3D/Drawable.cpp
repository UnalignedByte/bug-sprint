//
//  Drawable.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 21/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Drawable.h"

#include "Model.h"

using namespace std;


Drawable::Drawable()
{
}


Drawable::Drawable(const string &modelFileName)
{
    model = make_shared<Model>(modelFileName);
}


Drawable::Drawable(const string &modelFileName, const string &textureFileName)
{
    model = make_shared<Model>(modelFileName);
    texture = make_shared<Texture>(textureFileName);
}


Drawable::Drawable(const std::string &modelFileName,
                   const std::string &rightTextureFileName, const std::string &leftTextureFileName,
                   const std::string &topTextureFileName, const std::string &bottomTextureFileName,
                   const std::string &frontTextureFileName, const std::string backTextureFileName)
{
    model = make_shared<Model>(modelFileName);
    texture = make_shared<Texture>(rightTextureFileName, leftTextureFileName, topTextureFileName, bottomTextureFileName, frontTextureFileName, backTextureFileName);
}


GLsizei Drawable::getTrianglesCount() const
{
    return model->getTrianglesCount();
}


bool Drawable::getShouldCastShadow(shared_ptr<Light> light) const
{
    return shouldCastShadow;
}


void Drawable::setShouldCastShadow(bool shouldCastShadow)
{
    this->shouldCastShadow = shouldCastShadow;
}


shared_ptr<Model> Drawable::getModel() const
{
    return model;
}


shared_ptr<Texture> Drawable::getTexture() const
{
    return texture;
}


void Drawable::draw(shared_ptr<ShaderProgram> shaderProgram)
{
    for(shared_ptr<Instance> child : children) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(child))
            drawable->draw(shaderProgram);
    }

    if(texture)
        texture->use(shaderProgram);
    if(model)
        model->draw(shaderProgram, modelMatrix);
}


void Drawable::drawShadow(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Light> light)
{
    if(getShouldCastShadow(light)) {
        for(shared_ptr<Instance> child : children) {
            if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(child))
                drawable->drawShadow(shaderProgram, light);
        }

        if(model)
            model->draw(shaderProgram, modelMatrix);
    }
}
