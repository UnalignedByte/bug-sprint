//
// Created by Rafal Grodzinski on 06/11/2016.
//

#ifndef TYPES_H
#define TYPES_H

struct Input
{
    enum State {
        StateDown,
        StateUp,
        StateMoved,
        StateCanceled
    };

    float x = 0.0;
    float y = 0.0;
    float downX = 0.0;
    float downY = 0.0;

    State state = StateCanceled;
};

#endif
