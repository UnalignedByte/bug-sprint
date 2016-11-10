//
//  Light.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Light.h"

using namespace std;


Light::Light()
{
}


Vector3 Light::getLightDirection() const
{
    return Vector3({0.0, 0.0, -1.0});
}


void Light::updateLight(double timeInterval, shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    Vector3 lightDirection = getLightDirection();

    GLint lightDirectionId = glGetUniformLocation(shaderProgram->getId(), "lightDirection");
    glUniform3f(lightDirectionId, lightDirection[0], lightDirection[1], lightDirection[2]);
    
}
