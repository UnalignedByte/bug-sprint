//
//  Light.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Light.h"

#include <cmath>
#include <string>

using namespace std;


GLint Light::lightsCount = 0;


Light::Light(GLfloat viewWidth, GLfloat viewHeight, GLfloat cutOff) :
    viewWidth(viewWidth), viewHeight(viewHeight), cutOff(cutOff)
{
    if(cutOff <= 0.0)
        type = TypeDirectional;
    else
        type = TypeSpot;

    lightIndex = lightsCount++;
}


Color Light::getColor() const
{
    return color;
}


void Light::setColor(const Color &color)
{
    this->color = color;
}


GLfloat Light::getAmbientIntensity() const
{
    return ambientIntensity;
}


void Light::setAmbientIntensity(GLfloat ambientIntensity)
{
    this->ambientIntensity = ambientIntensity;
}


GLfloat Light::getDiffuseIntensity() const
{
    return diffuseIntensity;
}


void Light::setDiffuseIntensity(GLfloat diffuseIntensity)
{
    this->diffuseIntensity = diffuseIntensity;
}


GLfloat Light::getSpecularIntensity() const
{
    return specularIntensity;
}


void Light::setSpecularIntensity(GLfloat specularIntensity)
{
    this->specularIntensity = specularIntensity;
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

        string lightIndexString = "lights[" + to_string(lightIndex) + "].";

        // Type
        GLint lightTypeId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "type").c_str());
        glUniform1i(lightTypeId, type);

        // Position
        GLint lightPositionId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "position").c_str());
        Vector3 worldPosition = getWorldPosition();
        glUniform3f(lightPositionId, worldPosition[0], worldPosition[1], worldPosition[2]);

        // Direction
        GLint lightDirectionId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "direction").c_str());
        Vector3 direction = getDirection();
        glUniform3f(lightDirectionId, direction[0], direction[1], direction[2]);

        // Color
        GLint lightColorId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "color").c_str());
        glUniform3f(lightColorId, color[0], color[1], color[2]);

        // Ambient intensity
        GLint ambientIntensityId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "ambientIntensity").c_str());
        glUniform1f(ambientIntensityId, ambientIntensity);

        // Diffuse intensity
        GLint diffuseIntensityId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "diffuseIntensity").c_str());
        glUniform1f(diffuseIntensityId, diffuseIntensity);

        // Specular intensity
        GLint specularIntensityId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "specularIntensity").c_str());
        glUniform1f(specularIntensityId, specularIntensity);

        // Cut Off
        GLint cutOffId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "cutOff").c_str());
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
