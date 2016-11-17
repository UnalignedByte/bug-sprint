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


void Camera::updateCamera(double timeInterval, shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    GLint viewMatrixId = glGetUniformLocation(shaderProgram->getId(), "viewMatrix");
    Matrix4 viewMatrix = Matrix4::lookAt(translation, target);
    glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, viewMatrix.getData());

    GLint projectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "projectionMatrix");
    Matrix4 projectionMatrix = Matrix4::perspectiveProjection(fov, viewWidth/viewHeight, zNear, zFar);
    glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, projectionMatrix.getData());

    GLint eyePositionId = glGetUniformLocation(shaderProgram->getId(), "eyePosition");
    glUniform3f(eyePositionId, translation[0], translation[1], translation[2]);
}
