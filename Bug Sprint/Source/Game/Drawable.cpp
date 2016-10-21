//
//  Drawable.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 21/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Drawable.h"

#include "Model.h"


Drawable::Drawable(const string &modelFileName, shared_ptr<ShaderProgram> shaderProgram) :
    shaderProgram(shaderProgram), model(modelFileName)
{
}


void Drawable::draw()
{
    model.draw(shaderProgram, modelMatrix);
}
