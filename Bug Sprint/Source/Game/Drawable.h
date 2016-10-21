//
//  Drawable.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 21/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Instance.h"

#include <string>
#include <memory>

#include "Model.h"


class Drawable: public Instance
{
public:
    Drawable(const string &modelFileName, shared_ptr<ShaderProgram> shaderProgram);

    void draw() override;

protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
    Model model;
};

#endif
