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

    void touchDown(int x, int y);
    void touchUp(int x, int y);
    void touchMove(int x, int y);
    void touchCancel();

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
