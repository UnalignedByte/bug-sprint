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
#include "ShaderProgram.h"
#include "Instance.h"
#include "Drawable.h"
#include "Camera.h"
#include "Texture.h"
#include "Sprite.h"

using namespace std;


Core::Core(double width, double height) :
    width(width), height(height)
{
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
    instances[0]->translation[0] = -3.0;
    instances[0]->translation[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/monkey.obj", defaultPerFragmentShader));
    instances[1]->translation[0] = 0.0;
    instances[1]->translation[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/box.obj", "Game/box.jpg", texturedShader));
    instances[2]->translation[0] = 3.0;
    instances[2]->translation[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/plane.obj", defaultShadedPerFragmentShader));
    instances[3]->translation[1] = -1.0;

    instances.push_back(make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                              "Game/skybox_top.png", "Game/skybox_bottom.png",
                                              "Game/skybox_front.png", "Game/skybox_back.png",
                                              skyboxShader));
    dynamic_pointer_cast<Drawable>(instances.back())->setShouldCastShadow(false);

    instances2D.push_back(make_shared<Sprite>("Game/mario.png", spriteShader));
    instances2D.push_back(make_shared<Sprite>("Hello World!", "Fonts/BunakenUnderwater.ttf", 20.0, Color(1.0, 1.0, 0.0, 1.0), spriteShader));
    instances2D.push_back(make_shared<Sprite>("Game/goose.jpg", spriteShader));
}


void Core::update(double timeInterval, Input input)
{
    updateInput(timeInterval, input);
    updateState(timeInterval);
}


void Core::updateInput(double timeInterval, Input input)
{
    static Vector3 cameraStartPos;
    if(input.state == Input::StateDown) {
        cameraStartPos = camera->translation;
    } else if(input.state == Input::StateMoved) {
        camera->translation[0] = cameraStartPos[0] + (input.x - input.downX) * 3.0;
        camera->translation[1] = cameraStartPos[1] + (input.y - input.downY) * 3.0;
        camera->translation[2] = 0.0;
    }

    instances[0]->rotation[1] = instances[0]->rotation[1] + 45.0 * timeInterval;
    instances[1]->rotation[1] = instances[1]->rotation[1] + 45.0 * timeInterval;
    instances[2]->rotation[0] = instances[2]->rotation[0] + 45.0 * timeInterval;
    instances[2]->rotation[2] = instances[2]->rotation[2] + 30.0 * timeInterval;

    camera->target = Vector3{0.0, 0.0, 4.0};

    //light->translation = {camera->translation[0], camera->translation[1], 8.0};
    light->translation = {6.0, 2.0, 0.0};
    light->target = camera->target;

    auto inst = instances2D.back();
    static double elapsed;
    elapsed += timeInterval;
    inst->position[0] = width*0.5 * sin(elapsed / 2.0);
}


void Core::updateState(double timeInterval)
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
}


void Core::draw()
{
    shadowPass();
    renderPass();
}


void Core::shadowPass()
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
    glViewport(0, 0, width, height);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glCullFace(GL_BACK);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto instance : instances) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance)) {
            shadow->useShadow(drawable->getShader());
            drawable->draw();
        } else {
            instance->draw();
        }
    }

    // Draw Sprites
    glDisable(GL_DEPTH_TEST);

    for(auto instance : instances2D) {
        instance->draw();
    }
}
