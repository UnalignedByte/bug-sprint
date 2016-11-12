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
#include "Color.h"


class Light: public Instance
{
public:
    Light();


    Vector3 getDirection() const;
    void setDirection(const Vector3 &direction);
    Color getColor() const;
    void setColor(const Color &color);

    void updateLight(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    Vector3 direction = {0.0, 0.0, 1.0};
    Color color = {1.0, 1.0, 1.0, 1.0};
};

#endif
