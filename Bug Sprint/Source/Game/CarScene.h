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
#include "Car.h"
#include "Camera.h"


class CarScene: public Scene
{
public:
    CarScene(GLint viewWidth, GLint viewHeight);

    void updateInput(const Input &input) override;
    void update(float timeInterval) override;

protected:
    std::shared_ptr<Camera> camera;

    std::shared_ptr<Car> car;

    std::shared_ptr<Button> leftButton;
    std::shared_ptr<Button> rightButton;

protected:
    virtual void setupGame();
    virtual void setupUi();
};

#endif
