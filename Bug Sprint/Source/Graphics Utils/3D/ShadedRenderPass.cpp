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


void ShadedRenderPass::update()
{
    for(shared_ptr<Light> light : lights) {
        light->updateLight(shaderProgram);
        light->updateShadow(shaderProgram);
    }
}


void ShadedRenderPass::draw()
{
    glViewport(0, 0, viewWidth, viewHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
    glDisable(GL_BLEND);

    for(shared_ptr<Light> light : lights)
        light->useShadowTexture(shaderProgram);

    for(shared_ptr<Instance> instance : instances) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance))
            drawable->draw(shaderProgram);
    }
}
