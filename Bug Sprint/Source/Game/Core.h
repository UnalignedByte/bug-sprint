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

#include "ShaderProgram.h"
#include "Instance.h"
#include "Camera.h"
#include "Light.h"
#include "Color.h"
#include "Types.h"


class Core
{
public:
    Core(double width, double height);

    void update(double timeInterval, Input input);
    void draw();

private:
    Color clearColor{0.0, 0.0, 0.2, 1.0};

    std::shared_ptr<ShaderProgram> shader;
    std::shared_ptr<ShaderProgram> texturedShader;
    std::shared_ptr<ShaderProgram> skyboxShader;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Light> light;
    
    std::vector<std::shared_ptr<Instance>> instances;
};

#endif
