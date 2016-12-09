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


RenderPass2D::RenderPass2D() :
    shaderProgram(make_shared<ShaderProgram>("Shaders/sprite.vsh", "Shaders/sprite.fsh"))
{
}


void RenderPass2D::begin()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
}


void RenderPass2D::draw()
{
    shaderProgram->use();

    for(shared_ptr<Instance2D> instance : instances) {
        instance->draw();
    }
}


void RenderPass2D::addInstance(std::shared_ptr<Instance2D> instance)
{
    instances.insert(instance);
}


void RenderPass2D::removeInstance(std::shared_ptr<Instance2D> instance)
{
    instances.erase(instances.find(instance));
}
