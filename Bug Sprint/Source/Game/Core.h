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

#include "OpenGLES.h"
#include "ShaderProgram.h"
#include "Instance.h"
#include "Camera.h"
#include "Light.h"
#include "Color.h"
#include "Types.h"
#include "ShadowPass.h"


class Core
{
public:
    Core(double width, double height);

    void update(double timeInterval, Input input);
    void updateInput(double timeInterval, Input input);
    void updateState(double timeInterval);
    void draw();
    void shadowPass();
    void renderPass();

protected:
    Color clearColor{0.0, 0.0, 0.2, 1.0};
    GLint width;
    GLint height;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Camera> spriteCamera;
    std::shared_ptr<Light> light;
    std::shared_ptr<ShadowPass> shadow;
    
    std::vector<std::shared_ptr<Instance>> instances;
    std::vector<std::shared_ptr<Instance>> spriteInstances;

    std::vector<std::shared_ptr<ShaderProgram>> updateCameraShaders;
    std::vector<std::shared_ptr<ShaderProgram>> updateLightShaders;
    std::vector<std::shared_ptr<ShaderProgram>> updateShadowShaders;
    std::vector<std::shared_ptr<ShaderProgram>> shadedShaders;
    std::vector<std::shared_ptr<ShaderProgram>> updateSpriteCameraShaders;
};

#endif
