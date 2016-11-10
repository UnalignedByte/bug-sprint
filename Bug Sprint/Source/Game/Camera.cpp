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


Camera::Camera(GLfloat viewWidth, GLfloat viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
}


Matrix4 Camera::getCameraViewMatrix() const
{
    Matrix4 viewMatrix;
    viewMatrix = viewMatrix * Matrix4::translation(-translation[0], -translation[1], -translation[2]);

    Vector3 direction = target - translation;
    direction = direction.normalized();

    Vector3 right = direction.cross(Vector3{0.0, 1.0, 0.0});
    right = right.normalized();

    Vector3 up = right.cross(direction);

    Matrix4 lookAtMatrix{{right[0], up[0], direction[0], 0.0},
                         {right[1], up[1], direction[1], 0.0},
                         {right[2], up[2], direction[2], 0.0},
                         {0.0,      0.0,   0.0,          1.0}};

    viewMatrix = viewMatrix * lookAtMatrix;

    return viewMatrix;
}


Matrix4 Camera::getCameraProjectionMatrix() const
{
    return Matrix4::perspectiveProjection(fov, viewWidth/viewHeight, zNear, zFar);
}


void Camera::update(double timeInterval, shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    GLint viewMatrixId = glGetUniformLocation(shaderProgram->getId(), "viewMatrix");
    glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, getCameraViewMatrix().getData());

    GLint projectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, getCameraProjectionMatrix().getData());
}
