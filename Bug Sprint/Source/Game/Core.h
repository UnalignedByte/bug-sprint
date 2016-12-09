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
//#include "ShaderProgram.h"
//#include "Instance.h"
//#include "Instance2D.h"
//#include "Camera.h"
//#include "Light.h"
#include "Color.h"
#include "Types.h"
//#include "ShadowPass.h"
//#include "Button.h"
#include "Scene.h"


class Core
{
public:
    Core(int viewWidth, int viewHeight);

    //virtual void setupScene();

    virtual void update(double timeInterval, Input input);
    virtual void updateInput(float timeInterval, Input input);
    //void updateState(float timeInterval);
    virtual void draw();
    //void shadowPass();
    //void renderPass();

protected:
    Color clearColor{0.0, 0.0, 0.2, 1.0};
    GLint viewWidth;
    GLint viewHeight;
    GLfloat width;
    GLfloat height;

    std::shared_ptr<Scene> currentScene;


    /*std::shared_ptr<Camera> camera;
    std::shared_ptr<Camera> spriteCamera;
    std::shared_ptr<Light> light;
    std::shared_ptr<ShadowPass> shadow;
    std::shared_ptr<Button> buttonOne;
    
    std::vector<std::shared_ptr<Instance>> instances;
    std::vector<std::shared_ptr<Instance2D>> instances2D;

    std::vector<std::shared_ptr<ShaderProgram>> updateCameraShaders;
    std::vector<std::shared_ptr<ShaderProgram>> updateLightShaders;
    std::vector<std::shared_ptr<ShaderProgram>> updateShadowShaders;
    std::vector<std::shared_ptr<ShaderProgram>> shadedShaders;
    std::vector<std::shared_ptr<ShaderProgram>> updateSpriteCameraShaders;*/
};

#endif
