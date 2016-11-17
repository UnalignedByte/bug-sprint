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


Drawable::Drawable(const string &modelFileName, shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), model(modelFileName)
{
}


Drawable::Drawable(const string &modelFileName, const string &textureFileName, shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), model(modelFileName), texture(textureFileName)
{
}


Drawable::Drawable(const std::string &modelFileName,
                   const std::string &rightTextureFileName, const std::string &leftTextureFileName,
                   const std::string &topTextureFileName, const std::string &bottomTextureFileName,
                   const std::string &frontTextureFileName, const std::string backTextureFileName,
                   std::shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), model(modelFileName),
    texture(rightTextureFileName, leftTextureFileName, topTextureFileName, bottomTextureFileName, frontTextureFileName, backTextureFileName)
{
}


shared_ptr<ShaderProgram> Drawable::getShader() const
{
    return shaderProgram;
}


bool Drawable::getShouldCastShadow() const
{
    return shouldCastShadow;
}


void Drawable::setShouldCastShadow(bool shouldCastShadow)
{
    this->shouldCastShadow = shouldCastShadow;
}


void Drawable::draw()
{
    shaderProgram->use();
    texture.use(shaderProgram);
    model.draw(shaderProgram, modelMatrix);
}


void Drawable::drawShadow(shared_ptr<ShaderProgram> shaderProgram)
{
    if(!shouldCastShadow)
        return;
    
    shaderProgram->use();
    model.draw(shaderProgram, modelMatrix);
}
