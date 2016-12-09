//
//  Instance3D.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_3D_H
#define INSTANCE_3D_H

#include "Instance.h"

#include "OpenGLES.h"
#include "Vector.h"
#include "Matrix.h"


class Instance3D: public Instance
{
public:
    Vector3 position{0.0, 0.0, 0.0};
    Vector3 scale{1.0, 1.0, 1.0};
    Vector3 rotation{0.0, 0.0, 0.0};

public:
    void update(float timeInterval) override;
    void draw() override;
    GLsizei getTrianglesCount() const override;

protected:
    Matrix4 modelMatrix;
    GLsizei trianglesCount{0};
};

#endif
