//
//  Core.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Core.h"

#include "OpenGLES.h"

#include "Color.h"
//#include "ShaderProgram.h"
//#include "Instance.h"
//#include "Drawable.h"
//#include "Camera.h"
//#include "Texture.h"
///#include "Sprite.h"
#include "SystemUtils.h"
#include "TestScene.h"

using namespace std;


Core::Core(int viewWidth, int viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
    SystemUtils::Point size = SystemUtils::sizeForViewSize(viewWidth, viewHeight);
    width = size.x;
    height = size.y;

    currentScene = make_shared<TestScene>(width, height);
}

/*void Core::setupScene()
{
    currentScene = make_shared<TestScene>();
    shared_ptr<ShaderProgram> defaultShader = make_shared<ShaderProgram>("Shaders/default.vsh", "Shaders/default.fsh");
    shared_ptr<ShaderProgram> defaultPerFragmentShader = make_shared<ShaderProgram>("Shaders/defaultPerFragment.vsh", "Shaders/defaultPerFragment.fsh");
    shared_ptr<ShaderProgram> texturedShader = make_shared<ShaderProgram>("Shaders/textured.vsh", "Shaders/textured.fsh");
    shared_ptr<ShaderProgram> skyboxShader = make_shared<ShaderProgram>("Shaders/skybox.vsh", "Shaders/skybox.fsh");
    shared_ptr<ShaderProgram> defaultShadedPerFragmentShader = make_shared<ShaderProgram>("Shaders/defaultShadedPerFragment.vsh", "Shaders/defaultShadedPerFragment.fsh");
    shared_ptr<ShaderProgram> shadowShader = make_shared<ShaderProgram>("Shaders/shadow.vsh", "Shaders/shadow.fsh");
    shared_ptr<ShaderProgram> spriteShader = make_shared<ShaderProgram>("Shaders/sprite.vsh", "Shaders/sprite.fsh");

    updateCameraShaders.push_back(defaultShader);
    updateCameraShaders.push_back(defaultPerFragmentShader);
    updateCameraShaders.push_back(texturedShader);
    updateCameraShaders.push_back(skyboxShader);
    updateCameraShaders.push_back(defaultShadedPerFragmentShader);

    updateSpriteCameraShaders.push_back(spriteShader);

    updateLightShaders.push_back(defaultShader);
    updateLightShaders.push_back(defaultPerFragmentShader);
    updateLightShaders.push_back(texturedShader);
    updateLightShaders.push_back(defaultShadedPerFragmentShader);

    updateShadowShaders.push_back(shadowShader);
    //updateShadowShaders.push_back(texturedShader);
    updateShadowShaders.push_back(defaultShadedPerFragmentShader);

    shadedShaders.push_back(defaultShadedPerFragmentShader);

    camera = make_shared<Camera>(width, height, 10.0, 60.0);
    spriteCamera = make_shared<Camera>(width, height, 2.0);
    light = make_shared<Light>(width, height);
    shadow = make_shared<ShadowPass>(1024, 1024, shadowShader);

    instances.push_back(make_shared<Drawable>("Game/monkey_smooth.obj", defaultShadedPerFragmentShader));
    instances[0]->position[0] = -3.0;
    instances[0]->position[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/monkey.obj", defaultPerFragmentShader));
    instances[1]->position[0] = 0.0;
    instances[1]->position[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/box.obj", "Game/box.jpg", texturedShader));
    instances[2]->position[0] = 3.0;
    instances[2]->position[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/plane.obj", defaultShadedPerFragmentShader));
    instances[3]->position[1] = -1.0;

    instances.push_back(make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                              "Game/skybox_top.png", "Game/skybox_bottom.png",
                                              "Game/skybox_front.png", "Game/skybox_back.png",
                                              skyboxShader));
    dynamic_pointer_cast<Drawable>(instances.back())->setShouldCastShadow(false);

    instances2D.push_back(make_shared<Sprite>("Game/mario.png", spriteShader));
    instances2D.push_back(make_shared<Sprite>("Hello World!", "Fonts/BunakenUnderwater.ttf", 20.0, Color(1.0, 1.0, 0.0, 1.0), spriteShader));
    instances2D.push_back(make_shared<Sprite>("Game/goose.jpg", spriteShader));

    buttonOne = make_shared<Button>(spriteShader, "Game/button_up.png", "Game/button_down.png");
    buttonOne->position[0] = width/2.0 - buttonOne->getWidth()/2.0;
    buttonOne->position[1] = -height/2.0 + buttonOne->getHeight()/2.0;
    buttonOne->pressedCallback = [](){
        printf("Hello World!\n");
    };

    instances2D.push_back(buttonOne);*/
//}


void Core::update(double timeInterval, Input input)
{
    //updateInput(timeInterval, input);
    //updateState(timeInterval);

    currentScene->updateInput(input);
    currentScene->update(timeInterval);
}


/*void Core::updateInput(float timeInterval, Input input)
{
    currentScene->updateInput(timeInterval, input);
    static Vector3 cameraStartPos;
    if(input.state == Input::StateDown) {
        cameraStartPos = camera->position;
    } else if(input.state == Input::StateMoved) {
        camera->position[0] = cameraStartPos[0] + (input.x - input.downX) * 3.0;
        camera->position[1] = cameraStartPos[1] + (input.y - input.downY) * 3.0;
        camera->position[2] = 0.0;
    }

    buttonOne->updateInput(timeInterval, input);

    instances[0]->rotation[1] = instances[0]->rotation[1] + 45.0 * timeInterval;
    instances[1]->rotation[1] = instances[1]->rotation[1] + 45.0 * timeInterval;
    instances[2]->rotation[0] = instances[2]->rotation[0] + 45.0 * timeInterval;
    instances[2]->rotation[2] = instances[2]->rotation[2] + 30.0 * timeInterval;

    camera->setTarget(Vector3{0.0, 0.0, 4.0});

    //light->position = {camera->position[0], camera->position[1], 8.0};
    light->position = {6.0, 2.0, 0.0};
    light->setTarget(camera->getTarget());
}*/


/*void Core::updateState(float timeInterval)
{
    for(auto shader : updateCameraShaders)
        camera->updateCamera(timeInterval, shader);

    for(auto shader : updateLightShaders)
        light->updateLight(timeInterval, shader);

    for(auto shader : updateShadowShaders)
        light->updateShadow(timeInterval, shader);

    for(auto shader : updateSpriteCameraShaders)
        spriteCamera->updateCamera(timeInterval, shader);

    for(auto instance : instances)
        instance->update(timeInterval);

    for(auto instance : instances2D)
        instance->update(timeInterval);
}*/


void Core::draw()
{
    glViewport(0, 0, viewWidth, viewHeight);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentScene->draw();
}


/*void Core::shadowPass()
{
    shadow->begin();

    for(auto instance : instances)
    {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance)) {
            drawable->drawShadow(shadow->getShader());
        }
    }

    shadow->end();
}


void Core::renderPass()
{
    glViewport(0, 0, viewWidth, viewHeight);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw 3D
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glCullFace(GL_BACK);

    for(auto instance : instances) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance)) {
            shadow->useShadow(drawable->getShader());
            drawable->draw();
        } else {
            instance->draw();
        }
    }

    // Draw 2D
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    for(auto instance : instances2D) {
        instance->draw();
    }
}*/
