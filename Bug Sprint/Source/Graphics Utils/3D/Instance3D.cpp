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

    //modelMatrix = Matrix4();
    modelMatrix = modelMatrix * Matrix4::zRotation(rotation[2]);
    modelMatrix = modelMatrix * Matrix4::yRotation(rotation[1]);
    modelMatrix = modelMatrix * Matrix4::xRotation(rotation[0]);
    //modelMatrix = modelMatrix * Matrix4::scale(scale[0], scale[1], scale[2]);

    modelMatrix = modelMatrix * Matrix4::translation(position[0], position[1], position[2]);

    if(parent != nullptr) {
        if(Instance3D *parentInstance = dynamic_cast<Instance3D *>(parent)) {

            modelMatrix = modelMatrix * Matrix4::zRotation(parentInstance->rotation[2]);
            modelMatrix = modelMatrix * Matrix4::yRotation(parentInstance->rotation[1]);
            modelMatrix = modelMatrix * Matrix4::xRotation(parentInstance->rotation[0]);
            //modelMatrix = modelMatrix * Matrix4::scale(scale[0], scale[1], scale[2]);

            modelMatrix = modelMatrix * Matrix4::translation(parentInstance->position[0], parentInstance->position[1], parentInstance->position[2]);
        }
    }
}


GLsizei Instance3D::getTrianglesCount() const
{
    return Instance::getTrianglesCount() + trianglesCount;
}

Vector3 Instance3D::getWorldRotation() const
{
    Vector3 rotation = this->rotation;

    if(parent != nullptr) {
        if(Instance3D *parentInstance = dynamic_cast<Instance3D *>(parent))
            rotation = rotation + parentInstance->getWorldRotation();
    }

    return rotation;
}


Vector3 Instance3D::getWorldPosition() const
{
    Vector3 position = this->position;

    if(parent != nullptr) {
        if(Instance3D *parentInstance = dynamic_cast<Instance3D *>(parent))
            position = position + parentInstance->getWorldPosition();
    }

    return position;
}
