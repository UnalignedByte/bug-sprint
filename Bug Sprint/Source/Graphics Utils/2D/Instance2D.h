//
//  Instance2D.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 25/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_2D_H
#define INSTANCE_2D_H

#include "Instance.h"

#include "OpenGLES.h"
#include "Vector.h"
#include "Matrix.h"
#include <memory>
#include "ShaderProgram.h"


class Instance2D: public Instance
{
public:
    Vector2 position{0.0, 0.0};
    Vector2 scale{1.0, 1.0};
    GLfloat rotation{0};

public:
    void update(float timeInterval) override;
    virtual void draw(std::shared_ptr<ShaderProgram> shaderProgram);
    GLsizei getTrianglesCount() const override;

protected:
    Matrix4 modelMatrix;
    GLsizei trianglesCount{0};
};

#endif
