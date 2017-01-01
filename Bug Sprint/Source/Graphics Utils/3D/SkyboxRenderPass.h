//
//  SkyboxRenderPass.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 10/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SKYBOX_RENDER_PASS_H
#define SKYBOX_RENDER_PASS_H

#include "RenderPass.h"


class SkyboxRenderPass: public RenderPass
{
public:
    using RenderPass::RenderPass;

    void draw() override;
};

#endif
