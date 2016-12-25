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
GLuint Light::texture = 0;


Light::Light(GLint viewWidth, GLint viewHeight, GLfloat cutOff, GLfloat innerCutOff) :
    viewWidth(viewWidth), viewHeight(viewHeight), cutOff(cutOff), innerCutOff(innerCutOff)
{
    if(cutOff <= 0.0)
        type = TypeDirectional;
    else
        type = TypeSpot;

    if(innerCutOff < 0.0)
        this->innerCutOff = cutOff;

    lightIndex = lightsCount++;

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    if(texture == 0) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT16, viewWidth, viewHeight, 8, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, nullptr);
    }
    glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0, lightIndex);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw string("Could not create shadow framebuffer");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


Light::Type Light::getType() const
{
    return type;
}


GLint Light::getLightIndex() const
{
    return lightIndex;
}


bool Light::getShouldCastShadow() const
{
    return shouldCastShadow;
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
    return direction;
}


void Light::setDirection(Vector3 direction)
{
    this->direction = direction;
}


Vector3 Light::getWorldDirection() const
{
    Vector3 worldRotation = getWorldRotation();
    GLfloat yRotationInRadians = (M_PI * worldRotation[1])/180.0;
    GLfloat x = sin(yRotationInRadians) * direction[2];
    GLfloat z = cos(yRotationInRadians) * direction[2];

    x += cos(yRotationInRadians) * direction[0];
    z -= sin(yRotationInRadians) * direction[0];

    Vector3 worldDirection = {x, direction[1], z};

    return worldDirection.normalized();
}


Vector3 Light::getWorldTarget() const
{
    return worldTarget;
}


void Light::setWorldTarget(Vector3 worldTarget)
{
    this->worldTarget = worldTarget;
    this->direction = worldTarget - getWorldPosition();
}


void Light::updateLight(std::shared_ptr<ShaderProgram> shaderProgram)
{
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
    Vector3 direction = getWorldDirection();
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

    // Cut off
    GLint cutOffId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "cutOff").c_str());
    glUniform1f(cutOffId, cutOff);

    // Inner cut off
    GLint innerCutOffId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + "innerCutOff").c_str());
    glUniform1f(innerCutOffId, innerCutOff);
}


void Light::updateShadow(std::shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    string lightIndexString = "lights[" + to_string(lightIndex) + "].";

    GLint lightViewMatrixId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + ".viewMatrix").c_str());
    Matrix4 lightViewMatrix = Matrix4::lookAt(position, position + direction);
    glUniformMatrix4fv(lightViewMatrixId, 1, GL_FALSE, lightViewMatrix.getData());

    GLint lightProjectionMatrixId = glGetUniformLocation(shaderProgram->getId(), (lightIndexString + ".projectionMatrix").c_str());
    Matrix4 lightProjectionMatrix = Matrix4::perspectiveProjection(fov, viewWidth/viewHeight, zNear, zFar);
    glUniformMatrix4fv(lightProjectionMatrixId, 1, GL_FALSE, lightProjectionMatrix.getData());
}


void Light::useFramebuffer()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    glViewport(0, 0, viewWidth, viewHeight);
    glClear(GL_DEPTH_BUFFER_BIT);
}


void Light::useShadowTexture(std::shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    GLint shadowSamplerId  = glGetUniformLocation(shaderProgram->getId(), ("shadowSampler[" + to_string(lightIndex) + "]").c_str());
    glUniform1i(shadowSamplerId, 1);
}
