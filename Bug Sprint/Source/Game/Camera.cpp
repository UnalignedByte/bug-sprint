//
//  Camera.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 19/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Camera.h"

Camera::Camera(GLfloat viewWidth, GLfloat viewHeight) : viewWidth(viewWidth), viewHeight(viewHeight)
{
}


Matrix4 Camera::getCameraViewMatrix() const
{
    return Matrix4();
}


Matrix4 Camera::getCameraProjectionMatrix() const
{
    return Matrix4::perspectiveProjection(fov, viewWidth/viewHeight, zNear, zFar);
}
