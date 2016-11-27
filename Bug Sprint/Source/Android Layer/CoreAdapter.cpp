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


void CoreAdapter::touchDown(int x, int y)
{
    currentInput.state = Input::StateDown;

    Point pos = SystemUtils::positionForViewPosition(x, viewHeight - y);
    currentInput.downX = currentInput.x = pos.x;
    currentInput.downY = currentInput.y = pos.y;
}


void CoreAdapter::touchUp(int x, int y)
{
    currentInput.state = Input::StateUp;

    Point pos = SystemUtils::positionForViewPosition(x, viewHeight - y);
    currentInput.x = pos.x;
    currentInput.y = pos.y;
}


void CoreAdapter::touchMove(int x, int y)
{
    currentInput.state = Input::StateMoved;

    Point pos = SystemUtils::positionForViewPosition(x, viewHeight - y);
    currentInput.x = pos.x;
    currentInput.y = pos.y;
}


void CoreAdapter::touchCancel()
{
    currentInput.state = Input::StateCanceled;
}


void CoreAdapter::update(double timeInterval)
{
    try {
        core->update(timeInterval, currentInput);
    } catch(string exception) {
        handleException(exception);
    }
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
