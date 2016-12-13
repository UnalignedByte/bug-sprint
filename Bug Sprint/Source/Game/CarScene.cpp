//
//  CarScene.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "CarScene.h"

#include "RenderPass2D.h"
#include "ShaderProgram.h"
#include "Button.h"

using namespace std;


CarScene::CarScene(GLint viewWidth, GLint viewHeight) :
    Scene(viewWidth, viewHeight)
{
    setupUi();
}


void CarScene::setupUi()
{
    shared_ptr<ShaderProgram> shaderProgram = make_shared<ShaderProgram>("Shaders/shader2D.vsh", "Shaders/shader2D.fsh");
    shared_ptr<RenderPass2D> renderPass = make_shared<RenderPass2D>(width, height, shaderProgram);
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

    renderPasses.push_back(renderPass);
}
