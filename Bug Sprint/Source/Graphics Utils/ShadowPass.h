//
//  ShadowPass.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SHADOW_PASS_H
#define SHADOW_PASS_H

#include <memory>
#include "OpenGLES.h"
#include "ShaderProgram.h"


class ShadowPass
{
public:
    ShadowPass(GLint width, GLint height, std::shared_ptr<ShaderProgram> shaderProgram);

    std::shared_ptr<ShaderProgram> getShader() const;

    void useShadow(std::shared_ptr<ShaderProgram> shaderProgram) const;
    void begin();
    void end();

protected:
    GLint width;
    GLint height;

    GLuint framebuffer;
    GLuint texture;

    GLint previousFramebuffer;

    std::shared_ptr<ShaderProgram> shaderProgram;
};

#endif
