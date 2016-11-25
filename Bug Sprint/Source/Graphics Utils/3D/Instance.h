//
//  Instance.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include "OpenGLES.h"
#include "Vector.h"
#include "Matrix.h"


class Instance
{
public:
    Vector3 position{0.0, 0.0, 0.0};
    Vector3 scale{1.0, 1.0, 1.0};
    Vector3 rotation{0.0, 0.0, 0.0};

public:
    virtual void update(double timeInterval);
    virtual void draw();
    virtual GLsizei getTrianglesCount() const;

protected:
    Matrix4 modelMatrix;
    GLsizei trianglesCount{0};
};

#endif
