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
#include "ShaderProgram.h"
#include "Vector.h"
#include "Color.h"


class Light: public Instance
{
public:
    Light(GLfloat viewWidth, GLfloat viewHeight);

    Color getColor() const;
    void setColor(const Color &color);
    Vector3 getDirection() const;
    Vector3 getTarget() const;
    void setTarget(const Vector3 &target);

    void updateLight(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram);
    void updateShadow(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    Color color{1.0, 1.0, 1.0, 1.0};

    GLfloat viewWidth;
    GLfloat viewHeight;
    GLfloat fov{60.0};
    GLfloat zNear{0.01};
    GLfloat zFar{100.0};

    Vector3 target{0.0, 0.0, 1.0};
};

#endif
