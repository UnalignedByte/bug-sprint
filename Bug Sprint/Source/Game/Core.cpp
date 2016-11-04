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

    shader = make_shared<ShaderProgram>("default.vsh", "default.fsh");
    camera = make_shared<Camera>(width, height, shader);
    light = make_shared<Light>(shader);

    instances.push_back(make_shared<Drawable>("monkey.obj", shader));

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}


void Core::update(double timeInterval)
{
    camera->update(timeInterval);
    light->update(timeInterval);

    for(auto instance : instances) {
        instance->rotation[1] = instance->rotation[1] + 2.0;
        instance->translation[2] = 2.0;
        static GLfloat x=0.0;
        instance->translation[0] = sin(x / 100.0) * 2.0;
        x += 2.0;

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
