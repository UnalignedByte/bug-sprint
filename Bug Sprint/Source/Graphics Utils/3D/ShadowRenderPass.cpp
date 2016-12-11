//
//  ShadowRenderPass.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "ShadowRenderPass.h"

#include "Drawable.h"

using namespace std;


ShadowRenderPass::ShadowRenderPass(GLint viewWidth, GLint viewHeight, std::shared_ptr<ShaderProgram> shaderProgram) :
    RenderPass(viewWidth, viewHeight, shaderProgram)
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, viewWidth, viewHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, nullptr);

    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw string("Could not create shadow framebuffer");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void ShadowRenderPass::begin()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    glViewport(0, 0, viewWidth, viewHeight);
    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glCullFace(GL_FRONT);
}


void ShadowRenderPass::draw()
{
    for(shared_ptr<Instance> instance : instances) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance)) {
            drawable->drawShadow(shaderProgram);
        }
    }
}


void ShadowRenderPass::end()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, previousFramebuffer);
}


void ShadowRenderPass::useShadowTexture(std::shared_ptr<ShaderProgram> shaderProgram) const
{
    shaderProgram->use();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLint shadowSamplerId  = glGetUniformLocation(shaderProgram->getId(), "shadowSampler");
    glUniform1i(shadowSamplerId, 1);
}
