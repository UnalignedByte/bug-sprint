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


void ShadowRenderPass::update()
{
    for(shared_ptr<Light> light : lights) {
        light->updateLight(shaderProgram);
        light->updateShadow(shaderProgram);
    }
}


void ShadowRenderPass::draw()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glCullFace(GL_FRONT);

    for(shared_ptr<Light> light : lights) {
        shaderProgram->use();
        light->useFramebuffer();

        shaderProgram->use();
        GLint lightIndexId = glGetUniformLocation(shaderProgram->getId(), "lightIndex");
        glUniform1i(lightIndexId, light->getLightIndex());

        for(shared_ptr<Instance> instance : instances)
            instance->draw(shaderProgram);
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, previousFramebuffer);
}
