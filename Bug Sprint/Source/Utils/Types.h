//
// Created by Rafal Grodzinski on 06/11/2016.
//

#ifndef TYPES_H
#define TYPES_H

#include <map>

struct Input
{
    struct Touch {
        enum State {
            StateInvalid,
            StateDown,
            StateUp,
            StateMoved,
            StateCanceled
        };

        float x = 0.0;
        float y = 0.0;
        float downX = 0.0;
        float downY = 0.0;

        State state = StateInvalid;
    };

    std::map<int, Touch> touches;
};

#endif
