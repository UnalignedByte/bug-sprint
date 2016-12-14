//
//  ShadedRenderPass.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "ShadedRenderPass.h"

#include "Drawable.h"

using namespace std;


ShadedRenderPass::ShadedRenderPass(GLint viewWidth, GLint viewHeight, shared_ptr<ShaderProgram> shaderProgram,
                                   shared_ptr<ShadowRenderPass> shadowRenderPass) :
    RenderPass(viewWidth, viewHeight, shaderProgram),  shadowRenderPass(shadowRenderPass)
{
}


void ShadedRenderPass::begin()
{
    glViewport(0, 0, viewWidth, viewHeight);

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
}


void ShadedRenderPass::draw()
{
    shaderProgram->use();

    shadowRenderPass->useShadowTexture(shaderProgram);

    for(shared_ptr<Instance> instance : instances)
        instance->draw(shaderProgram);
}
