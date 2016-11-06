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

    double x = 0.0;
    double y = 0.0;
    double downX = 0.0;
    double downY = 0.0;

    State state = StateCanceled;
};

#endif
