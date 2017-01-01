//
//  RenderPass.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 03/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include "OpenGLES.h"
#include <memory>
#include <set>
#include <vector>
#include "Instance.h"
#include "Light.h"
#include "ShaderProgram.h"

class Light; // TODO: No idea why this has to be here

class RenderPass
{
public:
    RenderPass(GLint viewWidth, GLint viewHeight, std::shared_ptr<ShaderProgram> shaderProgram);

    virtual std::shared_ptr<ShaderProgram> getShaderProgram() const;

    virtual void addInstance(std::shared_ptr<Instance> instance);
    virtual void removeInstance(std::shared_ptr<Instance> instance);

    virtual void addLight(std::shared_ptr<Light> light);

    virtual void update();    
    virtual void draw();

protected:
    GLint viewWidth;
    GLint viewHeight;
    GLfloat width;
    GLfloat height;
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::set<std::shared_ptr<Instance>> instances;
    std::vector<std::shared_ptr<Light>> lights;
};

#endif
