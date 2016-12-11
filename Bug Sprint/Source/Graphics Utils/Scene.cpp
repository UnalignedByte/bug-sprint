//
//  Scene.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 01/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Scene.h"

#include "SystemUtils.h"

using namespace std;


Scene::Scene(GLint viewWidth, GLint viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
    SystemUtils::Point size = SystemUtils::sizeForViewSize(viewWidth, viewHeight);
    width = size.x;
    height = size.y;
}


void Scene::updateInput(Input input)
{
    for(shared_ptr<Instance> instance : instances)
        instance->updateInput(input);
}


void Scene::update(float timeInterval)
{
    for(shared_ptr<Instance> instance : instances)
        instance->update(timeInterval);

    for(shared_ptr<Light> light : lights) {
        light->updateLight();
        light->updateShadow();
    }

    for(shared_ptr<Camera> camera : cameras)
        camera->updateCamera();
}


void Scene::draw()
{
    for(shared_ptr<RenderPass> renderPass : renderPasses) {
        renderPass->begin();
        renderPass->draw();
        renderPass->end();
    }
}


void Scene::addInstance(std::shared_ptr<Instance> instance)
{
    instances.insert(instance);
}


void Scene::removeInstance(std::shared_ptr<Instance> instance)
{
    instances.erase(instances.find(instance));

    // Remove from render passes
    for(shared_ptr<RenderPass> renderPass : renderPasses)
        renderPass->removeInstance(instance);
}
