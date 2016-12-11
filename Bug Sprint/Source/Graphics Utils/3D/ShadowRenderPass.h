//
//  ShadowRenderPass.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SHADOW_PASS_H
#define SHADOW_PASS_H

#include "RenderPass.h"


class ShadowRenderPass: public RenderPass
{
public:
    ShadowRenderPass(GLint viewWidth, GLint viewHeight, std::shared_ptr<ShaderProgram> shaderProgram);

    void begin() override;
    void draw() override;
    void end() override;

    virtual void useShadowTexture(std::shared_ptr<ShaderProgram> shaderProgram) const;

protected:
    GLuint framebuffer;
    GLuint texture;

    GLint previousFramebuffer;
};

#endif
