//
//  Core.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Core.h"

#include "OpenGLES.h"

#include "SystemUtils.h"
#include "TestScene.h"
#include "CarScene.h"

using namespace std;


Core::Core(int viewWidth, int viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
    SystemUtils::Point size = SystemUtils::sizeForViewSize(viewWidth, viewHeight);
    width = size.x;
    height = size.y;

    currentScene = make_shared<CarScene>(viewWidth, viewHeight);
    //currentScene = make_shared<TestScene>(viewWidth, viewHeight);
}


void Core::update(double timeInterval, const Input &input)
{
    currentScene->updateInput(input);
    currentScene->update(timeInterval);
}


void Core::draw()
{
    glViewport(0, 0, viewWidth, viewHeight);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentScene->draw();
}
