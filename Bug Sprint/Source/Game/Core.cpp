//
//  Core.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Core.h"

#include <OpenGLES/ES3/gl.h>

using namespace std;


Core::Core(double width, double height)
{
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    prg = make_shared<ShaderProgram>("default.vsh", "default.fsh");
    box = make_shared<Model>("monkey.obj", prg);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}


void Core::update(double timeInterval)
{
}


void Core::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);

    box->draw();

    glFlush();
}
