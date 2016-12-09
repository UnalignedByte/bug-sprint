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
    return (target - position).normalized();
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

        GLint lightDirectionId = glGetUniformLocation(shaderProgram->getId(), "light.direction");
        Vector3 direction = getDirection();
        glUniform3f(lightDirectionId, direction[0], direction[1], direction[2]);

        GLint lightColorId = glGetUniformLocation(shaderProgram->getId(), "light.color");
        glUniform3f(lightColorId, color[0], color[1], color[2]);
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
