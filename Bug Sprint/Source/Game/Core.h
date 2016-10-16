//
//  Core.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CORE_H
#define CORE_H

#include "Color.h"


class Core
{
public:
    Core(double width, double height);

    void update(double timeInterval);
    void draw();

private:
    Color clearColor{0.1, 0.0, 0.0, 1.0};
};

#endif
