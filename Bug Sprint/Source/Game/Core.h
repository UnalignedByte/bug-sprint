//
//  Core.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CORE_H
#define CORE_H

#include <memory>
#include <vector>

#include "Color.h"
#include "ShaderProgram.h"
#include "Instance.h"
#include "Camera.h"


class Core
{
public:
    Core(double width, double height);

    void update(double timeInterval);
    void draw();

private:
    Color clearColor{0.1, 0.0, 0.0, 1.0};

    std::shared_ptr<ShaderProgram> shader;
    std::shared_ptr<Camera> camera;
    std::vector<Instance> instances;
};

#endif
