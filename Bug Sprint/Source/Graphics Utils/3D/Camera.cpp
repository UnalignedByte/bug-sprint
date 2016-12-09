//
//  Camera.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 19/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Camera.h"

#include "Matrix.h"

using namespace std;


Camera::Camera(GLfloat width, GLfloat height, GLfloat depth, GLfloat fieldOfView) :
    width(width), height(height), aspectRatio(width/height), zFar(zNear+ depth)
{
    if(fieldOfView <= 0.0) {
        fieldOfView = -1.0;
        type = TypeOrtographic;
    } else {
        this->fieldOfView = fieldOfView;
        type = TypePerspective;
    }
}


Camera::Type Camera::getType() const
{
    return type;
}


GLfloat Camera::getWidth() const
{
    return width;
}


GLfloat Camera::getHeight() const
{
    return height;
}


GLfloat Camera::getDepth() const
{
    return zFar - zNear;
}


GLfloat Camera::getFieldOfView() const
{
    return fieldOfView;
}


Vector3 Camera::getTarget() const
{
    return target;
}


void Camera::setTarget(const Vector3 &target)
{
    this->target = target;
}


void Camera::addRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    renderPasses.insert(renderPass);
}


void Camera::removeRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    renderPasses.erase(renderPasses.find(renderPass));
}


void Camera::updateCamera()
{
    for(shared_ptr<RenderPass> renderPass : renderPasses) {
        shared_ptr<ShaderProgram> shaderProgram = renderPass->getShaderProgram();

        shaderProgram->use();

        GLint viewMatrixId = glGetUniformLocation(shaderProgram->getId(), "viewMatrix");
        Matrix4 viewMatrix = Matrix4::lookAt(position, target);
        glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, viewMatrix.getData());

        GLint projectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "projectionMatrix");
        Matrix4 projectionMatrix;

        if(type == TypeOrtographic) {
            projectionMatrix = Matrix4::ortographicProjection(-width/2.0, width/2.0, -height/2.0, height/2.0,
                                                              zNear, zFar);
        } else {
            projectionMatrix = Matrix4::perspectiveProjection(fieldOfView, aspectRatio, zNear, zFar);
        }

        glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, projectionMatrix.getData());

        GLint eyePositionId = glGetUniformLocation(shaderProgram->getId(), "eyePosition");
        glUniform3f(eyePositionId, position[0], position[1], position[2]);
    }
}
