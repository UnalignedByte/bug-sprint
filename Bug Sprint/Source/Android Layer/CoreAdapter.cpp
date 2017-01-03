//
// Created by Rafal Grodzinski on 03/11/2016.
//

#include "CoreAdapter.h"

#include <android/log.h>
#include <stdlib.h>
#include <time.h>
#include "SystemUtils.h"

using namespace std;


CoreAdapter::CoreAdapter(int viewWidth, int viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
    try {
        SystemUtils::viewWidth = viewWidth;
        SystemUtils::viewHeight = viewHeight;

        core = new Core(viewWidth, viewHeight);
    } catch(string exception) {
        handleException(exception);
    }
}


CoreAdapter::~CoreAdapter()
{
    delete core;
}


void CoreAdapter::executeLoop()
{
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    double currentTime = time.tv_sec + time.tv_nsec/1.0e9;

    double timeInterval = currentTime - previousTime;
    if(previousTime == 0.0)
        timeInterval = 0.0;

    update(timeInterval);
    draw();

    previousTime = currentTime;
}


void CoreAdapter::touchDownWithId(int touchId, int x, int y)
{
    SystemUtils::Point pos = SystemUtils::positionForViewPosition(x, viewHeight - y);
    Input::Touch touch;
    touch.state = Input::Touch::StateDown;
    touch.downX = touch.x = pos.x;
    touch.downY = touch.y = pos.y;

    currentInput.touches[touchId] = touch;
}


void CoreAdapter::touchUpWithId(int touchId, int x, int y)
{
    SystemUtils::Point pos = SystemUtils::positionForViewPosition(x, viewHeight - y);
    Input::Touch touch;
    touch.state = Input::Touch::StateUp;
    touch.x = pos.x;
    touch.y = pos.y;

    currentInput.touches[touchId] = touch;
}


void CoreAdapter::touchMoveWithId(int touchId, int x, int y)
{
    // Is there a pending touch down event?
    if(currentInput.touches[touchId].state == Input::Touch::StateDown)
        return;

    SystemUtils::Point pos = SystemUtils::positionForViewPosition(x, viewHeight - y);
    Input::Touch touch;
    touch.state = Input::Touch::StateMoved;
    touch.x = pos.x;
    touch.y = pos.y;

    currentInput.touches[touchId] = touch;
}


void CoreAdapter::touchCancelWithId(int touchId)
{
    Input::Touch touch;
    touch.state = Input::Touch::StateCanceled;

    currentInput.touches[touchId] = touch;
}


void CoreAdapter::update(double timeInterval)
{
    try {
        core->update(timeInterval, currentInput);
    } catch(string exception) {
        handleException(exception);
    }

    // Remove events
    currentInput.touches.clear();
}


void CoreAdapter::draw()
{
    try {
        core->draw();
    } catch(string exception) {
        handleException(exception);
    }
}


void CoreAdapter::handleException(string exception)
{
#pragma clang diagnostics push
#pragma clang diagnostic ignored "-Wformat-security"
    __android_log_print(ANDROID_LOG_ERROR, "App", exception.c_str());
#pragma clang diagnostics pop

    abort();
}
