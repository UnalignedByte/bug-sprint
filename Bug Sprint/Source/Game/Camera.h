//
//  Camera.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 19/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "Instance.h"

#include <memory>
#include "OpenGLES.h"

#include "ShaderProgram.h"
#include "Matrix.h"


class Camera: public Instance
{
public:
    Vector3 target;

public:
    Camera(GLfloat viewWidth, GLfloat viewHeight);

    Matrix4 getCameraViewMatrix() const;
    Matrix4 getCameraProjectionMatrix() const;

    void updateCamera(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    GLfloat viewWidth;
    GLfloat viewHeight;
    GLfloat fov = 60.0;
    GLfloat zNear = 0.01;
    GLfloat zFar = 100.0;
};

#endif
