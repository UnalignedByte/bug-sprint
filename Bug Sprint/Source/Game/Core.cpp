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

using namespace std;


Core::Core(double width, double height)
{
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    shader = make_shared<ShaderProgram>("Shaders/default.vsh", "Shaders/default.fsh");
    camera = make_shared<Camera>(width, height, shader);
    light = make_shared<Light>(shader);

    instances.push_back(make_shared<Drawable>("Game/monkey.obj", shader));

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}


void Core::update(double timeInterval, Input input)
{
    static Vector3 cameraStartPos;
    if(input.state == Input::StateDown) {
         cameraStartPos = camera->translation;
    } else if(input.state == Input::StateMoved) {
        camera->translation[0] = cameraStartPos[0] + input.x - input.downX;
        camera->translation[1] = cameraStartPos[1] + input.y - input.downY;
        camera->translation[2] = 0.0;
    }

    camera->target = Vector3{0.0, 0.0, 2.0};

    camera->update(timeInterval);
    light->update(timeInterval);

    for(auto instance : instances) {
        instance->rotation[1] = instance->rotation[1] + 2.0;
        instance->translation[2] = 4.0;
        //static GLfloat x=0.0;
        //instance->translation[0] = sin(x / 100.0) * 2.0;
        //x += 2.0;

        instance->update(timeInterval);
    }
}


void Core::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);

    for(auto instance: instances)
        instance->draw();

    glFlush();
}
