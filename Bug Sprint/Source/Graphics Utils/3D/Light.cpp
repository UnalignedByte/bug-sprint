//
//  Light.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Light.h"

#include <cmath>

using namespace std;


Light::Light(GLfloat viewWidth, GLfloat viewHeight, GLint lightIndex, GLfloat cutOff) :
    viewWidth(viewWidth), viewHeight(viewHeight), lightIndex(lightIndex), cutOff(cutOff)
{
    if(cutOff <= 0.0)
        type = TypeDirectional;
    else
        type = TypeSpotlight;
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
    Vector3 worldRotation = getWorldRotation();
    GLfloat yRotationInRadians = (M_PI * worldRotation[1])/180.0;
    Vector3 dir = target - position;
    GLfloat x = sin(yRotationInRadians) * dir[2];
    GLfloat z = cos(yRotationInRadians) * dir[2];

    x += cos(yRotationInRadians) * dir[0];
    z -= sin(yRotationInRadians) * dir[0];

    dir = {x, dir[1], z};
    return (dir).normalized();
}


Vector3 Light::getTarget() const
{
    return target;
}


void Light::setTarget(const Vector3 &target)
{
    this->target = target;
}


void Light::addRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    renderPasses.insert(renderPass);
}


void Light::removeRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    renderPasses.erase(renderPasses.find(renderPass));
}


void Light::addShadowRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    shadowRenderPasses.insert(renderPass);
}


void Light::removeShadowRenderPass(std::shared_ptr<RenderPass> renderPass)
{
    shadowRenderPasses.erase(renderPasses.find(renderPass));
}


void Light::updateLight()
{
    for(shared_ptr<RenderPass> renderPass : renderPasses) {
        shared_ptr<ShaderProgram> shaderProgram = renderPass->getShaderProgram();

        shaderProgram->use();

        // Type
        GLint lightTypeId = -1;
        if(lightIndex == 0)
            lightTypeId = glGetUniformLocation(shaderProgram->getId(), "light0.type");
        else
            lightTypeId = glGetUniformLocation(shaderProgram->getId(), "light1.type");
        glUniform1i(lightTypeId, type);

        // Position
        GLint lightPositionId = -1;
        if(lightIndex == 0)
            lightPositionId = glGetUniformLocation(shaderProgram->getId(), "light0.position");
        else
            lightPositionId = glGetUniformLocation(shaderProgram->getId(), "light1.position");
        Vector3 worldPosition = getWorldPosition();
        glUniform3f(lightPositionId, worldPosition[0], worldPosition[1], worldPosition[2]);

        // Direction
        GLint lightDirectionId = -1;
        if(lightIndex == 0)
            lightDirectionId = glGetUniformLocation(shaderProgram->getId(), "light0.direction");
        else
            lightDirectionId = glGetUniformLocation(shaderProgram->getId(), "light1.direction");
        Vector3 direction = getDirection();
        glUniform3f(lightDirectionId, direction[0], direction[1], direction[2]);

        // Color
        GLint lightColorId = -1;
        if(lightIndex == 0)
            lightColorId = glGetUniformLocation(shaderProgram->getId(), "light0.color");
        else
            lightColorId = glGetUniformLocation(shaderProgram->getId(), "light1.color");
        glUniform3f(lightColorId, color[0], color[1], color[2]);

        // Cut Off
        GLint cutOffId = -1;
        if(lightIndex == 0)
            cutOffId = glGetUniformLocation(shaderProgram->getId(), "light0.cutOff");
        else
            cutOffId = glGetUniformLocation(shaderProgram->getId(), "light1.cutOff");
        glUniform1f(cutOffId, cutOff);
    }
}


void Light::updateShadow()
{
    for(shared_ptr<RenderPass> renderPass : shadowRenderPasses) {
        shared_ptr<ShaderProgram> shaderProgram = renderPass->getShaderProgram();
        
        shaderProgram->use();

        GLint lightViewMatrixId = glGetUniformLocation(shaderProgram->getId(), "lightViewMatrix");
        Matrix4 lightViewMatrix = Matrix4::lookAt(position, target);
        glUniformMatrix4fv(lightViewMatrixId, 1, GL_FALSE, lightViewMatrix.getData());

        GLint lightProjectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "lightProjectionMatrix");
        Matrix4 lightProjectionMatrix = Matrix4::perspectiveProjection(fov, viewWidth/viewHeight, zNear, zFar);
        glUniformMatrix4fv(lightProjectionMatrixId, 1, GL_FALSE, lightProjectionMatrix.getData());
    }
}
