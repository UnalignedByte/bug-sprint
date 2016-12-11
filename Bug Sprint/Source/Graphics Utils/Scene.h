//
//  Scene.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 01/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <set>
#include "Types.h"
#include "RenderPass.h"
#include "Instance.h"
#include "Camera.h"
#include "Light.h"


class Scene
{
public:
    explicit Scene(GLint viewWidth, GLint viewHeight);

    virtual void addInstance(std::shared_ptr<Instance> instance);
    virtual void removeInstance(std::shared_ptr<Instance> instance);

    virtual void updateInput(Input input);
    virtual void update(float timeInterval);
    virtual void draw();

protected:
    GLint viewWidth;
    GLint viewHeight;
    GLfloat width;
    GLfloat height;

    std::set<std::shared_ptr<Instance>> instances;
    std::set<std::shared_ptr<RenderPass>> renderPasses;
    std::set<std::shared_ptr<Light>> lights;
    std::set<std::shared_ptr<Camera>> cameras;
};

#endif
