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
    using RenderPass::RenderPass;

    void update() override;
    void draw() override;

protected:
    GLint previousFramebuffer;
};

#endif
