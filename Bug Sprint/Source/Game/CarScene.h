//
//  CarScene.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CAR_SCENE_H
#define CAR_SCENE_H

#include "Scene.h"

#include <memory>
#include "Button.h"


class CarScene: public Scene
{
public:
    CarScene(GLint viewWidth, GLint viewHeight);

protected:
    std::shared_ptr<Button> leftButton;
    std::shared_ptr<Button> rightButton;

protected:
    virtual void setupUi();
};

#endif
