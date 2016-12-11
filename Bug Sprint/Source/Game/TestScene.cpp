//
//  TestScene.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "TestScene.h"

#include "ShaderProgram.h"
#include "Drawable.h"
#include "SkyboxRenderPass.h"
#include "ShadedRenderPass.h"
#include "ShadowRenderPass.h"

using namespace std;


TestScene::TestScene(GLint viewWidth, GLint viewHeight) :
    Scene(viewWidth, viewHeight)
{
    // Setup Shaders
    shared_ptr<ShaderProgram> shadedShader = make_shared<ShaderProgram>("Shaders/defaultShadedPerFragment.vsh",
                                                                        "Shaders/defaultShadedPerFragment.fsh");
    shared_ptr<ShaderProgram> shadowShader = make_shared<ShaderProgram>("Shaders/shadow.vsh", "Shaders/shadow.fsh");
    shared_ptr<ShaderProgram> skyboxShader = make_shared<ShaderProgram>("Shaders/skybox.vsh", "Shaders/skybox.fsh");

    //shared_ptr<ShaderProgram> spriteShader = make_shared<ShaderProgram>("Shaders/sprite.vsh", "Shaders/sprite.fsh");

    // Setup Render Passes
    shared_ptr<SkyboxRenderPass> skyboxRenderPass = make_shared<SkyboxRenderPass>(viewWidth, viewHeight, skyboxShader);
    shared_ptr<ShadowRenderPass> shadowRenderPass = make_shared<ShadowRenderPass>(2048, 2048, shadowShader);
    shared_ptr<ShadedRenderPass> shadedRenderPass = make_shared<ShadedRenderPass>(viewWidth, viewHeight, shadedShader,
                                                                                  shadowRenderPass);

    renderPasses.insert(shadowRenderPass);
    renderPasses.insert(shadedRenderPass);
    renderPasses.insert(skyboxRenderPass);

    // Setup Instances

    // Monkey left
    shared_ptr<Drawable> monkeySmooth = make_shared<Drawable>("Game/monkey_smooth.obj");
    monkeySmooth->position[0] = -3.0;
    monkeySmooth->position[2] = 4.0;
    addInstance(monkeySmooth);
    shadowRenderPass->addInstance(monkeySmooth);
    shadedRenderPass->addInstance(monkeySmooth);

    // Monkey center
    monkey = make_shared<Drawable>("Game/monkey.obj");
    addInstance(monkey);
    shadowRenderPass->addInstance(monkey);
    shadedRenderPass->addInstance(monkey);

    // Box
    shared_ptr<Drawable> box = make_shared<Drawable>("Game/box.obj", "Game/box.jpg");
    box->position[0] = 3.0;
    box->position[2] = 4.0;
    addInstance(box);
    shadowRenderPass->addInstance(box);
    shadedRenderPass->addInstance(box);

    // Plane
    shared_ptr<Drawable> plane = make_shared<Drawable>("Game/plane.obj");
    plane->position[1] = -1.0;
    addInstance(plane);
    shadedRenderPass->addInstance(plane);

    // Skybox
    shared_ptr<Instance> skybox = make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                                        "Game/skybox_top.png", "Game/skybox_bottom.png",
                                                        "Game/skybox_front.png", "Game/skybox_back.png");
    skyboxRenderPass->addInstance(skybox);
    addInstance(skybox);

    // Light
    light = make_shared<Light>(width, height);
    light->position = {6.0, 2.0, 0.0};
    lights.insert(light);
    light->addRenderPass(shadedRenderPass);
    light->addShadowRenderPass(shadedRenderPass);
    light->addShadowRenderPass(shadowRenderPass);

    // Cameras
    camera = make_shared<Camera>(width, height, 10.0, 60.0);
    camera->addRenderPass(shadedRenderPass);
    camera->addRenderPass(skyboxRenderPass);
    cameras.insert(camera);
}


void TestScene::updateInput(Input input)
{
    static Vector3 cameraStartPos;

    if(input.state == Input::StateDown) {
        cameraStartPos = camera->position;
    } else if(input.state == Input::StateMoved) {
        camera->position[0] = cameraStartPos[0] + (input.x - input.downX) * 3.0;
        camera->position[1] = cameraStartPos[1] + (input.y - input.downY) * 3.0;
        camera->position[2] = 0.0;
    }
}


void TestScene::update(float timeInterval)
{
    Scene::update(timeInterval);

     //buttonOne->updateInput(timeInterval, input);

     monkey->rotation[1] = monkey->rotation[1] + 45.0 * timeInterval;
    monkey->position[2] = 4.0;

     camera->setTarget(Vector3{0.0, 0.0, 4.0});

     //light->position = {camera->position[0], camera->position[1], 8.0};
     light->position = {6.0, 2.0, 0.0};
     light->setTarget(camera->getTarget());
}
