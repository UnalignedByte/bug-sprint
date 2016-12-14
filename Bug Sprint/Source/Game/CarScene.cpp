//
//  CarScene.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "CarScene.h"

#include "ShadowRenderPass.h"
#include "ShadedRenderPass.h"
#include "RenderPass2D.h"
#include "ShaderProgram.h"

using namespace std;


CarScene::CarScene(GLint viewWidth, GLint viewHeight) :
    Scene(viewWidth, viewHeight)
{
    setupGame();
    setupUi();
}


void CarScene::setupGame()
{
    //Shadow
    shared_ptr<ShaderProgram> shadowShaderProgram = make_shared<ShaderProgram>("Shaders/shaderShadow.vsh", "Shaders/shaderShadow.fsh");
    shared_ptr<ShadowRenderPass> shadowRenderPass = make_shared<ShadowRenderPass>(2048, 2048, shadowShaderProgram);
    renderPasses.push_back(shadowRenderPass);

    // Shaded
    shared_ptr<ShaderProgram> shadedShaderProgram = make_shared<ShaderProgram>("Shaders/shaderShaded.vsh", "Shaders/shaderShaded.fsh");
    shared_ptr<ShadedRenderPass> shadedRenderPass = make_shared<ShadedRenderPass>(viewWidth, viewHeight, shadedShaderProgram, shadowRenderPass);
    renderPasses.push_back(shadedRenderPass);

    // Camera
    camera = make_shared<Camera>(width, height, 10.0f, 60.0f);
    cameras.push_back(camera);
    camera->addRenderPass(shadowRenderPass);
    camera->addRenderPass(shadedRenderPass);

    // Light
    shared_ptr<Light> light = make_shared<Light>(viewWidth, viewHeight);
    light->position = {6.0, 2.0, 0.0};
    lights.push_back(light);
    light->addRenderPass(shadedRenderPass);
    light->addShadowRenderPass(shadowRenderPass);
    light->addShadowRenderPass(shadedRenderPass);

    // Car
    car = make_shared<Car>();
    addInstance(car);
    shadedRenderPass->addInstance(car);

    // Ground
    shared_ptr<Drawable> ground = make_shared<Drawable>("Game/Things/ground.obj", "Game/Things/ground_diffuse@2x.png");
    addInstance(ground);
    shadedRenderPass->addInstance(ground);
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


void CarScene::updateInput(Input input)
{
    Scene::updateInput(input);

    car->isTurningLeft = leftButton->getState() == Button::StateDown && rightButton->getState() != Button::StateDown;
    car->isTurningRight = rightButton->getState() == Button::StateDown && leftButton->getState() != Button::StateDown;
    car->isAccelerating = leftButton->getState() == Button::StateDown || rightButton->getState() == Button::StateDown;
}


void CarScene::update(float timeInterval)
{
    camera->position = car->position + Vector3({0.5f, 3.0f, -3.5f});
    camera->setTarget(car->position);

    Scene::update(timeInterval);
}
