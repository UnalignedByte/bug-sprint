//
//  Drawable2D.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 01/01/2017.
//  Copyright © 2017 UnalignedByte. All rights reserved.
//

#ifndef DRAWABLE_2D
#define DRAWABLE_2D

#include "Instance2D.h"

#include <memory>
#include "ShaderProgram.h"


class Drawable2D: public Instance2D
{
public:
    virtual void draw(std::shared_ptr<ShaderProgram> shaderProgram);
};

#endif
