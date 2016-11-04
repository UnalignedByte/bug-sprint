//
// Created by Rafal Grodzinski on 03/11/2016.
//

#include "CoreAdapter.h"

#include <time.h>

using namespace std;


CoreAdapter::CoreAdapter(int width, int height)
{
    try {
        core = new Core(width, height);
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


void CoreAdapter::update(double timeInterval)
{
    try {
        core->update(timeInterval);
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
}
