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

ShadedRenderPass::ShadedRenderPass(GLint viewWidth, GLint viewHeight, GLfloat width, GLfloat height,
                                   shared_ptr<ShaderProgram> shaderProgram, shared_ptr<ShadowRenderPass> shadowRenderPass) :
    RenderPass(viewWidth, viewHeight, width, height, shaderProgram),  shadowRenderPass(shadowRenderPass)
{
}


void ShadedRenderPass::begin()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
}


void ShadedRenderPass::draw()
{
    shaderProgram->use();

    shadowRenderPass->useShadowTexture(shaderProgram);

    for(shared_ptr<Instance> instance : instances) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance)) {
            drawable->draw(shaderProgram);
        }
    }
}
