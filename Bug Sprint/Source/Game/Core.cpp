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

using namespace std;


Core::Core(double width, double height)
{
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    defaultShader = make_shared<ShaderProgram>("Shaders/default.vsh", "Shaders/default.fsh");
    defaultPerFragmentShader = make_shared<ShaderProgram>("Shaders/defaultPerFragment.vsh", "Shaders/defaultPerFragment.fsh");
    texturedShader = make_shared<ShaderProgram>("Shaders/textured.vsh", "Shaders/textured.fsh");
    skyboxShader = make_shared<ShaderProgram>("Shaders/skybox.vsh", "Shaders/skybox.fsh");

    camera = make_shared<Camera>(width, height);
    light = make_shared<Light>();

    instances.push_back(make_shared<Drawable>("Game/monkey_smooth.obj", defaultShader));
    instances[0]->translation[0] = -3.0;
    instances[0]->translation[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/monkey_smooth.obj", defaultPerFragmentShader));
    instances[1]->translation[0] = 0.0;
    instances[1]->translation[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/box.obj", "Game/box.jpg", texturedShader));
    instances[2]->translation[0] = 3.0;
    instances[2]->translation[2] = 4.0;

    instances.push_back(make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                              "Game/skybox_top.png", "Game/skybox_bottom.png",
                                              "Game/skybox_front.png", "Game/skybox_back.png",
                                              skyboxShader));

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}


void Core::update(double timeInterval, Input input)
{
    static Vector3 cameraStartPos;
    if(input.state == Input::StateDown) {
         cameraStartPos = camera->translation;
    } else if(input.state == Input::StateMoved) {
        camera->translation[0] = cameraStartPos[0] + (input.x - input.downX) * 3.0;
        camera->translation[1] = cameraStartPos[1] + (input.y - input.downY) * 3.0;
        camera->translation[2] = 0.0;
    }

    camera->target = Vector3{0.0, 0.0, 4.0};

    camera->updateCamera(timeInterval, defaultShader);
    camera->updateCamera(timeInterval, defaultPerFragmentShader);
    camera->updateCamera(timeInterval, texturedShader);
    camera->updateCamera(timeInterval, skyboxShader);

    light->updateLight(timeInterval, defaultShader);
    light->updateLight(timeInterval, defaultPerFragmentShader);
    light->updateLight(timeInterval, texturedShader);

    for(auto instance : instances) {
        instance->rotation[1] = instance->rotation[1] + 45.0 * timeInterval;

        instance->update(timeInterval);
    }
}


void Core::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto instance: instances)
        instance->draw();

    glFlush();
}
