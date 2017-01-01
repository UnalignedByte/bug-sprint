//
//  RenderPass2D.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 03/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "RenderPass2D.h"

#include "Drawable2D.h"

using namespace std;


void RenderPass2D::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    for(shared_ptr<Instance> instance : instances) {
        if(shared_ptr<Drawable2D> drawable = dynamic_pointer_cast<Drawable2D>(instance))
            drawable->draw(shaderProgram);
    }
}
