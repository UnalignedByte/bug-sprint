//
//  Instance3D.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Instance3D.h"

using namespace std;


void Instance3D::update(float timeInterval)
{
    modelMatrix = Matrix4();
    modelMatrix = modelMatrix * Matrix4::zRotation(rotation[2]);
    modelMatrix = modelMatrix * Matrix4::yRotation(rotation[1]);
    modelMatrix = modelMatrix * Matrix4::xRotation(rotation[0]);
    modelMatrix = modelMatrix * Matrix4::scale(scale[0], scale[1], scale[2]);
    modelMatrix = modelMatrix * Matrix4::translation(position[0], position[1], position[2]);
}


GLsizei Instance3D::getTrianglesCount() const
{
    return trianglesCount;
}
