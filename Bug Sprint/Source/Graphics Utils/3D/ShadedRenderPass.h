//
//  ShadedRenderPass.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SHADED_RENDER_PASS_H
#define SHADED_RENDER_PASS_H

#include "RenderPass.h"

#include "ShadowRenderPass.h"


class ShadedRenderPass: public RenderPass
{
public:
    ShadedRenderPass(GLint viewWidth, GLint viewHeight, std::shared_ptr<ShaderProgram> shaderProgram,
                     std::shared_ptr<ShadowRenderPass> shadowRenderPass);

    void begin() override;
    void draw() override;

protected:
    std::shared_ptr<ShadowRenderPass> shadowRenderPass;
};

#endif
