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


void TestScene::loadScene()
{
    // Setup Shaders
    shared_ptr<ShaderProgram> defaultShadedPerFragmentShader = make_shared<ShaderProgram>("Shaders/defaultShadedPerFragment.vsh",
                                                                                          "Shaders/defaultShadedPerFragment.fsh");
    shared_ptr<ShaderProgram> shadowShader = make_shared<ShaderProgram>("Shaders/shadow.vsh", "Shaders/shadow.fsh");
    shared_ptr<ShaderProgram> spriteShader = make_shared<ShaderProgram>("Shaders/sprite.vsh", "Shaders/sprite.fsh");
    shared_ptr<ShaderProgram> skyboxShader = make_shared<ShaderProgram>("Shaders/skybox.vsh", "Shaders/skybox.fsh");

    // Setup Instances
    shared_ptr<Instance> monkey = make_shared<Drawable>("Game/monkey.obj", defaultShadedPerFragmentShader);
    addInstance(monkey);

   /*shared_ptr<Instance> skybox = make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                                       "Game/skybox_top.png", "Game/skybox_bottom.png",
                                                       "Game/skybox_front.png", "Game/skybox_back.png");
    addInstance(skybox);*/

    // Setup Control Instances

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
}
