//
//  ShadedRenderPass.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "ShadedRenderPass.h"

#include "Drawable.h"
#include "Model.h"

using namespace std;

struct Vertex {
    GLfloat position[2];
    GLfloat texCoords[2];
};

ShadedRenderPass::ShadedRenderPass(GLint viewWidth, GLint viewHeight, shared_ptr<ShaderProgram> shaderProgram,
                                   shared_ptr<ShadowRenderPass> shadowRenderPass) :
    RenderPass(viewWidth, viewHeight, shaderProgram),  shadowRenderPass(shadowRenderPass)
{
    glGenFramebuffers(1, &bloomBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, bloomBufferId);
    glGenTextures(2, colorBuffers);

    GLuint depthTex;
    glGenTextures(1, &depthTex);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, viewWidth, viewHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

    for(int i=0; i<2; i++) {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewWidth, viewHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw string("Could not create framebuffer");

    bloomShader = make_shared<ShaderProgram>("Shaders/shaderBloom.vsh", "Shaders/shaderBloom.fsh");

    Vertex vertices[6] = {{{-1.0, -1.0}, {0.0f, 0.0f}},
                          {{+1.0, +1.0}, {1.0f, 1.0f}},
                          {{-1.0, +1.0}, {0.0f, 1.0f}},
                          {{-1.0, -1.0}, {0.0f, 0.0f}},
                          {{+1.0, -1.0}, {1.0f, 0.0f}},
                          {{+1.0, +1.0}, {1.0f, 1.0f}}};

    glGenVertexArrays(1, &outputVertexArrayId);
    glBindVertexArray(outputVertexArrayId);

    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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
    GLint prev;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev);

    glBindFramebuffer(GL_FRAMEBUFFER, bloomBufferId);
    GLuint attachements[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, attachements);

    glViewport(0, 0, viewWidth, viewHeight);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
    glDisable(GL_BLEND);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(shared_ptr<Light> light : lights)
        light->useShadowTexture(shaderProgram);

    for(shared_ptr<Instance> instance : instances) {
        if(shared_ptr<Drawable> drawable = dynamic_pointer_cast<Drawable>(instance))
            drawable->draw(shaderProgram);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, prev);
    bloomShader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
    GLint renderSamplerId = glGetUniformLocation(bloomShader->getId(), "renderSampler");
    glUniform1i(renderSamplerId, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[1]);
    GLint bloomSampler = glGetUniformLocation(bloomShader->getId(), "bloomSampler");
    glUniform1i(bloomSampler, 1);

    glBindVertexArray(outputVertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
}
