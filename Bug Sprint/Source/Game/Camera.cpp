//
//  Camera.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 19/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Camera.h"

#include "ShaderProgram.h"

using namespace std;


Camera::Camera(GLfloat viewWidth, GLfloat viewHeight, shared_ptr<ShaderProgram> shaderProgram) :
    viewWidth(viewWidth), viewHeight(viewHeight), shaderProgram(shaderProgram)
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


void Camera::update(double timeInterval)
{
    shaderProgram->use();

    GLint viewMatrixId = glGetUniformLocation(shaderProgram->getId(), "viewMatrix");
    glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, getCameraViewMatrix().getData());

    GLint projectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, getCameraProjectionMatrix().getData());
}
