//
//  Instance2D.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 25/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_2D_H
#define INSTANCE_2D_H

#include "OpenGLES.h"
#include "Vector.h"
#include "Matrix.h"


class Instance2D
{
public:
    Vector2 position{0.0, 0.0};
    Vector2 scale{1.0, 1.0};
    GLfloat rotation{0};

public:
    virtual void update(double timeInterval);
    virtual void draw();
    virtual GLsizei getTrianglesCount() const;

protected:
    Matrix4 modelMatrix;
    GLsizei trianglesCount{0};
};

#endif
