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
    void draw() override;

    virtual void addInstance(std::shared_ptr<Instance2D> instance);
    virtual void removeInstance(std::shared_ptr<Instance2D> instance);
    
protected:
    std::set<std::shared_ptr<Instance2D>> instances;
};

#endif
