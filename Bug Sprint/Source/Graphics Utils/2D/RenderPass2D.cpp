//
//  RenderPass2D.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 03/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "RenderPass2D.h"

#include "OpenGLES.h"

using namespace std;


void RenderPass2D::begin()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
}
