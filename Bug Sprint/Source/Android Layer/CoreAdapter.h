//
// Created by Rafal Grodzinski on 03/11/2016.
//

#ifndef COREADAPTER_H
#define COREADAPTER_H

#include <string>

#include "Core.h"


class CoreAdapter
{
public:
    CoreAdapter(int width, int height);
    virtual ~CoreAdapter();

    void executeLoop();

private:
    Core *core;
    double previousTime = 0.0;

    void update(double timeInterval);
    void draw();

    void handleException(std::string exception);
};

#endif
