//
//  Light.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef LIGHT_H
#define LIGHT_H

#include "Instance.h"

#include <memory>
#include "OpenGLES.h"

#include "ShaderProgram.h"
#include "Vector.h"


class Light: public Instance
{
public:
    Light();

    Vector3 getLightDirection() const;

    void update(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram);
};

#endif
