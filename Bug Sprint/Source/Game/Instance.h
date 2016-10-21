//
//  Instance.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <memory>

#include "Vector.h"
#include "Matrix.h"
#include "Model.h"
#include "ShaderProgram.h"


class Instance
{
public:
    Vector3 translation {0.0, 0.0, 0.0};
    Vector3 scale {1.0, 1.0, 1.0};
    Vector3 rotation {0.0, 0.0, 0.0};

public:
    Instance();

    virtual void update(double timeInterval);
    virtual void draw();

protected:
    Matrix4 modelMatrix;
};

#endif
