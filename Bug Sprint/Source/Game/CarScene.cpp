//
//  CarScene.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "CarScene.h"

#include "ShaderProgram.h"
#include "ShadowRenderPass.h"
#include "ShadedRenderPass.h"
#include "SkyboxRenderPass.h"
#include "RenderPass2D.h"
#include <iostream>

using namespace std;


CarScene::CarScene(GLint viewWidth, GLint viewHeight) :
    Scene(viewWidth, viewHeight)
{
    setupGame();
    setupUi();
}


void CarScene::setupGame()
{
    //Shadow render pass
    shared_ptr<ShaderProgram> shadowShaderProgram = make_shared<ShaderProgram>("Shaders/shaderShadow.vsh", "Shaders/shaderShadow.fsh");
    shared_ptr<ShadowRenderPass> shadowRenderPass = make_shared<ShadowRenderPass>(2048, 2048, shadowShaderProgram);
    renderPasses.push_back(shadowRenderPass);

    // Skybox render pass
    shared_ptr<ShaderProgram> skyboxShaderProgram = make_shared<ShaderProgram>("Shaders/shaderSkybox.vsh", "Shaders/shaderSkybox.fsh");
    shared_ptr<SkyboxRenderPass> skyboxRenderPass = make_shared<SkyboxRenderPass>(viewWidth, viewHeight, skyboxShaderProgram);
    renderPasses.push_back(skyboxRenderPass);

    // Shaded render pass
    shared_ptr<ShaderProgram> shadedShaderProgram = make_shared<ShaderProgram>("Shaders/shaderShaded.vsh", "Shaders/shaderShaded.fsh");
    shared_ptr<ShadedRenderPass> shadedRenderPass = make_shared<ShadedRenderPass>(viewWidth, viewHeight, shadedShaderProgram, shadowRenderPass);
    renderPasses.push_back(shadedRenderPass);

    // Camera
    camera = make_shared<Camera>(width, height, 10.0f, 60.0f);
    cameras.push_back(camera);
    camera->addRenderPass(shadedRenderPass);
    camera->addRenderPass(skyboxRenderPass);

    // Light
    shared_ptr<Light> light = make_shared<Light>(1024);
    light->position = {10.0, 10.0, 0.0};
    light->setWorldTarget({0.0, 0.0, 0.0});
    light->setDiffuseIntensity(0.8);
    shadowRenderPass->addLight(light);
    shadedRenderPass->addLight(light);

    // Car
    car = make_shared<Car>(viewWidth, viewHeight);
    car->position = {0.0, 1.0, 0.0};
    addInstance(car);
    shadedRenderPass->addInstance(car);
    shadowRenderPass->addInstance(car);
    for(shared_ptr<Light> light : car->getLights()) {
        shadowRenderPass->addLight(light);
        shadedRenderPass->addLight(light);
    }

    // Ground
    shared_ptr<Drawable> ground = make_shared<Drawable>("Game/Things/ground.obj", "Game/Things/ground_diffuse@2x.png");
    ground->position = {0.0, 0.0, 0.0};
    ground->getModel()->setAmbientIntensity(1.0);
    ground->getModel()->setSpecularIntensity(100);
    addInstance(ground);
    shadedRenderPass->addInstance(ground);
    shadowRenderPass->addInstance(ground);

    // Trees
    shared_ptr<Drawable> tree0 = make_shared<Drawable>("Game/Things/tree.obj");
    addInstance(tree0);
    shadedRenderPass->addInstance(tree0);
    shadowRenderPass->addInstance(tree0);

    shared_ptr<Drawable> tree1 = make_shared<Drawable>("Game/Things/tree.obj");
    tree1->position = {2.0, 0.0, 2.0};
    addInstance(tree1);
    shadedRenderPass->addInstance(tree1);
    shadowRenderPass->addInstance(tree1);

    shared_ptr<Drawable> tree2 = make_shared<Drawable>("Game/Things/tree.obj");
    tree2->position = {4.0, 0.0, 2.4};
    addInstance(tree2);
    shadedRenderPass->addInstance(tree2);
    shadowRenderPass->addInstance(tree2);

    shared_ptr<Drawable> tree3 = make_shared<Drawable>("Game/Things/tree.obj");
    tree3->position = {-3.0, 0.0, -1.0};
    addInstance(tree3);
    shadedRenderPass->addInstance(tree3);
    shadowRenderPass->addInstance(tree3);

    shared_ptr<Drawable> tree4 = make_shared<Drawable>("Game/Things/tree.obj");
    tree4->position = {1.0, 0.0, 4.0};
    addInstance(tree4);
    shadedRenderPass->addInstance(tree4);
    shadowRenderPass->addInstance(tree4);

    // Skybox
    shared_ptr<Drawable> skybox = make_shared<Drawable>("Game/box.obj", "Game/skybox_right.png", "Game/skybox_left.png",
                                                        "Game/skybox_top.png", "Game/skybox_bottom.png",
                                                        "Game/skybox_front.png", "Game/skybox_back.png");
    skyboxRenderPass->addInstance(skybox);
    addInstance(skybox);

    auto uniforms = shadedShaderProgram->getActiveUniforms();
    for(auto uniform : uniforms) {
        cout << uniform << endl;
    }
}


void CarScene::setupUi()
{
    shared_ptr<ShaderProgram> shaderProgram = make_shared<ShaderProgram>("Shaders/shader2D.vsh", "Shaders/shader2D.fsh");
    shared_ptr<RenderPass2D> renderPass = make_shared<RenderPass2D>(width, height, shaderProgram);
    renderPasses.push_back(renderPass);
    shared_ptr<Camera> camera = make_shared<Camera>(width, height, 2.0);
    cameras.push_back(camera);
    camera->addRenderPass(renderPass);

    // Left Button
    leftButton = make_shared<Button>("Game/UI/button_left_up@2x.png",
                                     "Game/UI/button_left_down@2x.png");
    leftButton->position = {(-width + leftButton->getWidth()*1.5f) / 2.0f,
                            (-height + leftButton->getHeight()*1.5f) / 2.0f};
    leftButton->setRange(leftButton->getWidth());

    addInstance(leftButton);
    renderPass->addInstance(leftButton);

    // Right Button
    rightButton = make_shared<Button>("Game/UI/button_right_up@2x.png",
                                     "Game/UI/button_right_down@2x.png");
    rightButton->position = {(width - rightButton->getWidth()*1.5f) / 2.0f,
        (-height + rightButton->getHeight()*1.5f) / 2.0f};
    rightButton->setRange(leftButton->getWidth());

    addInstance(rightButton);
    renderPass->addInstance(rightButton);
}


void CarScene::updateInput(const Input &input)
{
    Scene::updateInput(input);

    car->isTurningLeft = leftButton->getState() == Button::StateDown && rightButton->getState() != Button::StateDown;
    car->isTurningRight = rightButton->getState() == Button::StateDown && leftButton->getState() != Button::StateDown;
    car->isAccelerating = leftButton->getState() == Button::StateDown || rightButton->getState() == Button::StateDown;
}


void CarScene::update(float timeInterval)
{
    camera->position = car->position + Vector3({10.1f, 15.0f, -10.1f});
    camera->setTarget(car->position);

    Scene::update(timeInterval);
}
