//
//  Instance.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_H
#define INSTANCE_H

#include <memory>
#include "OpenGLES.h"
#include "Types.h"
#include "ShaderProgram.h"


class Instance
{
public:
    virtual void updateInput(const Input &input);
    virtual void update(float timeInterval);
    virtual void draw(std::shared_ptr<ShaderProgram> shaderProgram);

    virtual GLsizei getTrianglesCount() const;
};

#endif
