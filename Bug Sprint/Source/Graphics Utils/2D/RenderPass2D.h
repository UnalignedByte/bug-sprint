//
//  RenderPass2D.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 03/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef RENDER_PASS_2D
#define RENDER_PASS_2D

#include "RenderPass.h"

#include <memory>
#include <set>
#include "ShaderProgram.h"
#include "Instance2D.h"


class RenderPass2D: public RenderPass
{
public:
    using RenderPass::RenderPass;

    void begin() override;
};

#endif
