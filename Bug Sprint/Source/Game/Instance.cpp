//
//  Instance.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Instance.h"

using namespace std;


Instance::Instance()
{
}


Instance::Instance(const string &fileName, shared_ptr<ShaderProgram> shaderProgram)
{
    model = make_shared<Model>(fileName, shaderProgram);
}


void Instance::setViewMatrix(const Matrix4 &viewMatrix)
{
    this->viewMatrix = viewMatrix;
}


void Instance::setProjectionMatrix(const Matrix4 &projectionMatrix)
{
    this->projectionMatrix = projectionMatrix;
}


void Instance::update(double timeInterval)
{
    modelMatrix = Matrix4();
    modelMatrix = modelMatrix * Matrix4::zRotation(rotation[2]);
    modelMatrix = modelMatrix * Matrix4::yRotation(rotation[1]);
    modelMatrix = modelMatrix * Matrix4::xRotation(rotation[0]);
    modelMatrix = modelMatrix * Matrix4::translation(translation[0], translation[1], translation[2]);
}


void Instance::draw()
{
    model->draw(modelMatrix, viewMatrix, projectionMatrix);
}
