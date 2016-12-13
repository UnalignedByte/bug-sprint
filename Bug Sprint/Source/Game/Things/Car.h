//
//  Car.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CAR_H
#define CAR_H

#include "Instance3D.h"

#include <string>
#include <array>
#include "Drawable.h"
#include "ShaderProgram.h"


class Car: public Instance3D
{
public:
    bool isAccelerating{false};
    bool isTurningLeft{false};
    bool isTurningRight{false};
    bool isBreaking{false};

public:
    Car();

    void update(float timeInterval) override;

protected:
    GLfloat speed{0};
    GLfloat wheelsTurn{0};

    std::shared_ptr<Drawable> body;
    std::array<std::shared_ptr<Drawable>, 4> wheels;
};

#endif
