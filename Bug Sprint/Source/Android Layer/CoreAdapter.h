//
// Created by Rafal Grodzinski on 03/11/2016.
//

#ifndef COREADAPTER_H
#define COREADAPTER_H

#include <string>

#include "Core.h"
#include "Types.h"


class CoreAdapter
{
public:
    CoreAdapter(int viewWidth, int viewHeight);
    virtual ~CoreAdapter();

    void executeLoop();

    void touchDownWithId(int touchId, int x, int y);
    void touchUpWithId(int touchId, int x, int y);
    void touchMoveWithId(int touchId, int x, int y);
    void touchCancelWithId(int touchId);

private:
    Core *core;

    int viewWidth;
    int viewHeight;
    Input currentInput;

    double previousTime = 0.0;

    void update(double timeInterval);
    void draw();

    void handleException(std::string exception);
};

#endif
