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
#include <vector>
#include "OpenGLES.h"
#include "Types.h"
#include "ShaderProgram.h"


class Instance
{
public:
    virtual void updateInput(const Input &input);
    virtual void update(float timeInterval);
    virtual void draw(std::shared_ptr<ShaderProgram> shaderProgram);

    virtual void addChild(std::shared_ptr<Instance>);

    virtual GLsizei getTrianglesCount() const;

protected:
    std::vector<std::shared_ptr<Instance>> children;
    Instance *parent{nullptr};
};

#endif
