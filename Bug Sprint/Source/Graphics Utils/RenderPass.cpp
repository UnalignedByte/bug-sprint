//
//  RenderPass.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 03/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "RenderPass.h"

using namespace std;


RenderPass::RenderPass(GLint viewWidth, GLint viewHeight, GLfloat width, GLfloat height, shared_ptr<ShaderProgram> shaderProgram) :
    viewWidth(viewWidth), viewHeight(viewHeight), width(width), height(height), shaderProgram(shaderProgram)
{
}


void RenderPass::begin()
{
}


void RenderPass::draw()
{
    shaderProgram->use();

    for(shared_ptr<Instance> instance : instances)
    instance->draw();
}


void RenderPass::end()
{
}


shared_ptr<ShaderProgram> RenderPass::getShaderProgram() const
{
    return shaderProgram;
}


void RenderPass::addInstance(std::shared_ptr<Instance> instance)
{
    instances.insert(instance);
}


void RenderPass::removeInstance(std::shared_ptr<Instance> instance)
{
    instances.erase(instances.find(instance));
}
