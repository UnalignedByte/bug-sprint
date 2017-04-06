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
    glGenFramebuffers(1, &bloomBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, bloomBufferId);
    GLuint colorBuffers[2];
    glGenTextures(2, colorBuffers);
    for(int i=0; i<2; i++) {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, viewWidth, viewHeight, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }
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
    glBindFramebuffer(GL_FRAMEBUFFER, bloomBufferId);
    GLuint attachements[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, attachements);

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
