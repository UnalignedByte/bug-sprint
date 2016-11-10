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


void Drawable::draw()
{
    shaderProgram->use();
    texture.use(shaderProgram);
    model.draw(shaderProgram, modelMatrix);
}
