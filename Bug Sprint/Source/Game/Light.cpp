//
//  Light.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Light.h"

using namespace std;


struct LightUniform {
    GLfloat direction[3];
    GLfloat color[3];
};


Light::Light()
{
}


Vector3 Light::getDirection() const
{
    return direction;
}


void Light::setDirection(const Vector3 &direction)
{
    this->direction = direction.normalized();
}


Color Light::getColor() const
{
    return color;
}


void Light::setColor(const Color &color)
{
    this->color = color;
}


void Light::updateLight(double timeInterval, shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    GLint lightDirectionId = glGetUniformLocation(shaderProgram->getId(), "light.direction");
    glUniform3f(lightDirectionId, direction[0], direction[1], direction[2]);

    GLint lightColorId = glGetUniformLocation(shaderProgram->getId(), "light.color");
    glUniform3f(lightColorId, color[0], color[1], color[2]);
}
