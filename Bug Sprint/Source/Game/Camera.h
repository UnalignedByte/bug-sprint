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
    enum Type {
        TypeOrtographic,
        TypePerspective
    };

public:
    Vector3 target;

public:
    Camera(GLfloat width, GLfloat height, GLfloat depth, GLfloat fieldOfView = -1.0);

    Type getType() const;
    GLfloat getWidth() const;
    GLfloat getHeight() const;
    GLfloat getDepth() const;
    GLfloat getFieldOfView() const;

    void updateCamera(double timeInterval, std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    Type type;

    GLfloat width;
    GLfloat height;
    GLfloat aspectRatio;
    GLfloat zNear = 0.01;
    GLfloat zFar;
    GLfloat fieldOfView;
};

#endif
