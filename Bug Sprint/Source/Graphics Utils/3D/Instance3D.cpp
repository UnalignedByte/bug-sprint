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
    Instance::update(timeInterval);

    modelMatrix = Matrix4();
    modelMatrix = modelMatrix * Matrix4::zRotation(rotation[2]);
    modelMatrix = modelMatrix * Matrix4::yRotation(rotation[1]);
    modelMatrix = modelMatrix * Matrix4::xRotation(rotation[0]);
    modelMatrix = modelMatrix * Matrix4::scale(scale[0], scale[1], scale[2]);

    Vector3 translation = getWorldPosition();
    modelMatrix = modelMatrix * Matrix4::translation(translation[0], translation[1], translation[2]);
}


GLsizei Instance3D::getTrianglesCount() const
{
    return Instance::getTrianglesCount() + trianglesCount;
}


Vector3 Instance3D::getWorldPosition() const
{
    Vector3 position = this->position;

    if(parent != nullptr) {
        if(Instance3D *parentInstance = dynamic_cast<Instance3D *>(parent)) {
            position = position + parentInstance->position;
        }
    }

    return position;
}
