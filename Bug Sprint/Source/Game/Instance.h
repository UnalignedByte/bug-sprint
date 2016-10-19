//
//  Instance.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <memory>

#include "Vector.h"
#include "Matrix.h"
#include "Model.h"
#include "ShaderProgram.h"


class Instance
{
public:
    Vector3 translation;
    Vector3 rotation;

public:
    Instance();
    Instance(const std::string &fileName, std::shared_ptr<ShaderProgram> shaderProgram);

    virtual void update(double timeInterval);
    virtual void draw();

    virtual void setViewMatrix(const Matrix4 &viewMatrix);
    virtual void setProjectionMatrix(const Matrix4 &projectionMatrix);

private:
    Matrix4 modelMatrix;
    Matrix4 viewMatrix;
    Matrix4 projectionMatrix;

    std::shared_ptr<Model> model;
};

#endif
