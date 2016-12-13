//
//  Car.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Car.h"

using namespace std;


Car::Car()
{
    body = make_shared<Drawable>("Game/Things/car_body.obj");
    addChild(body);
}


void Car::update(float timeInterval)
{
    Instance3D::update(timeInterval);
}
