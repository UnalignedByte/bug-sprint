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
#include "ShadowRenderPass.h"
#include "ShadedRenderPass.h"

using namespace std;


TestScene::TestScene(GLint viewWidth, GLint viewHeight) :
    Scene(viewWidth, viewHeight)
{
}


void TestScene::loadScene()
{
    // Setup Shaders
    shared_ptr<ShaderProgram> defaultShadedPerFragmentShader = make_shared<ShaderProgram>("Shaders/defaultShadedPerFragment.vsh",
                                                                                          "Shaders/defaultShadedPerFragment.fsh");
    shared_ptr<ShaderProgram> shadowShader = make_shared<ShaderProgram>("Shaders/shadow.vsh", "Shaders/shadow.fsh");
    shared_ptr<ShaderProgram> spriteShader = make_shared<ShaderProgram>("Shaders/sprite.vsh", "Shaders/sprite.fsh");
    shared_ptr<ShaderProgram> skyboxShader = make_shared<ShaderProgram>("Shaders/skybox.vsh", "Shaders/skybox.fsh");

    // Setup Instances
    monkey = make_shared<Drawable>("Game/monkey.obj");
    addInstance(monkey);

   /*shared_ptr<Instance> skybox = make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                                       "Game/skybox_top.png", "Game/skybox_bottom.png",
                                                       "Game/skybox_front.png", "Game/skybox_back.png");
    addInstance(skybox);*/

    // Setup Render Passes
    shared_ptr<ShadowRenderPass> shadowRenderPass = make_shared<ShadowRenderPass>(viewWidth, viewHeight,
                                                                                  width, height, shadowShader);
    shadowRenderPass->addInstance(monkey);

    shared_ptr<ShadedRenderPass> shadedRenderPass = make_shared<ShadedRenderPass>(viewWidth, viewHeight,
                                                                                  width, height, shadowShader,
                                                                                  shadowRenderPass);
    shadedRenderPass->addInstance(monkey);

    renderPasses.insert(shadowRenderPass);
    renderPasses.insert(shadedRenderPass);

    // Light
    shared_ptr<Light> light = make_shared<Light >(width, height);
    lights.insert(light);
    light->addRenderPass(shadedRenderPass);
    light->addShadowRenderPass(shadedRenderPass);

    // Cameras
    shared_ptr<Camera> camera = make_shared<Camera>(width, height, 10.0, 60.0);
    camera->addRenderPass(shadedRenderPass);
    cameras.insert(camera);
}


void TestScene::update(float timeInterval)
{
    Scene::update(timeInterval);

    static Vector3 cameraStartPos;
     /*if(input.state == Input::StateDown) {
     cameraStartPos = camera->position;
     } else if(input.state == Input::StateMoved) {
     camera->position[0] = cameraStartPos[0] + (input.x - input.downX) * 3.0;
     camera->position[1] = cameraStartPos[1] + (input.y - input.downY) * 3.0;
     camera->position[2] = 0.0;
     }*/

     //buttonOne->updateInput(timeInterval, input);

     monkey->rotation[1] = monkey->rotation[1] + 45.0 * timeInterval;

     camera->setTarget(Vector3{0.0, 0.0, 4.0});

     //light->position = {camera->position[0], camera->position[1], 8.0};
     light->position = {6.0, 2.0, 0.0};
     light->setTarget(camera->getTarget());
}
