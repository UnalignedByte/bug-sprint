//
//  Core.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CORE_H
#define CORE_H

#include <memory>
#include <vector>

#include "OpenGLES.h"
#include "Color.h"
#include "Types.h"
#include "Scene.h"


class Core
{
public:
    Core(int viewWidth, int viewHeight);

    virtual void update(double timeInterval, Input input);
    virtual void draw();

protected:
    Color clearColor{0.0, 0.0, 0.2, 1.0};
    GLint viewWidth;
    GLint viewHeight;
    GLfloat width;
    GLfloat height;

    std::shared_ptr<Scene> currentScene;
};

#endif
