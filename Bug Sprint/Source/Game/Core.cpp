//
//  Core.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Core.h"

#include <OpenGLES/ES3/gl.h>


Core::Core(double width, double height)
{
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}


void Core::update(double timeInterval)
{
}


void Core::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
