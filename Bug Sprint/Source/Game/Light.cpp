//
//  Light.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Light.h"

using namespace std;


Light::Light(GLfloat viewWidth, GLfloat viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
}


Color Light::getColor() const
{
    return color;
}


void Light::setColor(const Color &color)
{
    this->color = color;
}


Vector3 Light::getDirection() const
{
    return (target - translation).normalized();
}


void Light::updateLight(double timeInterval, shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    GLint lightDirectionId = glGetUniformLocation(shaderProgram->getId(), "light.direction");
    Vector3 direction = getDirection();
    glUniform3f(lightDirectionId, direction[0], direction[1], direction[2]);

    GLint lightColorId = glGetUniformLocation(shaderProgram->getId(), "light.color");
    glUniform3f(lightColorId, color[0], color[1], color[2]);
}


void Light::updateShadow(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    GLint lightViewMatrixId = glGetUniformLocation(shaderProgram->getId(), "lightViewMatrix");
    Matrix4 lightViewMatrix = Matrix4::lookAt(translation, target);
    glUniformMatrix4fv(lightViewMatrixId, 1, GL_FALSE, lightViewMatrix.getData());

    GLint lightProjectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "lightProjectionMatrix");
    Matrix4 lightProjectionMatrix = Matrix4::perspectiveProjection(fov, viewWidth/viewHeight, zNear, zFar);
    glUniformMatrix4fv(lightProjectionMatrixId, 1, GL_FALSE, lightProjectionMatrix.getData());
}
