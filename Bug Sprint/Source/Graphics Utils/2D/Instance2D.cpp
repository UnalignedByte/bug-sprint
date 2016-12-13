//
//  Instance2D.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 25/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Instance2D.h"

using namespace std;


void Instance2D::update(float timeInterval)
{
    modelMatrix = Matrix4();
    modelMatrix = modelMatrix * Matrix4::zRotation(rotation);
    modelMatrix = modelMatrix * Matrix4::scale(scale[0], scale[1], 1.0);
    modelMatrix = modelMatrix * Matrix4::translation(position[0], position[1], 0.0);
}


GLfloat Instance2D::getWidth() const
{
    return width;
}


GLfloat Instance2D::getHeight() const
{
    return height;
}


GLsizei Instance2D::getTrianglesCount() const
{
    return trianglesCount;
}
