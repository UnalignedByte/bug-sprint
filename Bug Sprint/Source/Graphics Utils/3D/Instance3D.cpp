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

    Vector3 worldRotation = getWorldRotation();
    modelMatrix = modelMatrix * Matrix4::zRotation(worldRotation[2]);
    modelMatrix = modelMatrix * Matrix4::yRotation(worldRotation[1]);
    modelMatrix = modelMatrix * Matrix4::xRotation(worldRotation[0]);
    modelMatrix = modelMatrix * Matrix4::scale(scale[0], scale[1], scale[2]);

    Vector3 worldTranslation = getWorldPosition();
    modelMatrix = modelMatrix * Matrix4::translation(worldTranslation[0], worldTranslation[1], worldTranslation[2]);
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
