//
//  Car.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Car.h"

#include <iostream>

using namespace std;


static GLfloat kAcceleration = 0.05;
static GLfloat kMaxSpeed = 0.3;
static GLfloat kSlowdownSpeed = 0.05;
static GLfloat kWheelsTurnSpeed = 0.5;
static GLfloat kMaxWheelsTurn = 5.0;


Car::Car(GLint viewWidth, GLint viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
    body = make_shared<Drawable>("Game/Things/car_body.obj");
    body->getModel().setColor(Color(1.0, 0.0, 0.0));
    body->getModel().setDiffuseIntensity(1.0);
    body->getModel().setSpecularIntensity(2.0);
    addChild(body);

    wheels[0] = make_shared<Drawable>("Game/Things/car_wheel.obj");
    wheels[0]->position = {-1.0, -0.25, 1.5};
    addChild(wheels[0]);

    wheels[1] = make_shared<Drawable>("Game/Things/car_wheel.obj");
    wheels[1]->position = {1.0, -0.25, 1.5};
    addChild(wheels[1]);

    wheels[2] = make_shared<Drawable>("Game/Things/car_wheel.obj");
    wheels[2]->position = {-1.0, -0.25, -1.5};
    addChild(wheels[2]);

    wheels[3] = make_shared<Drawable>("Game/Things/car_wheel.obj");
    wheels[3]->position = {1.0, -0.25, -1.5};
    addChild(wheels[3]);

    // Headlights
    lights[0] = make_shared<Light>(viewWidth, viewHeight, 20.0, 15.0);
    lights[0]->setDirection({0.0, 0.0, 1.0});
    lights[0]->position = {0.0, 0.0, 0.0};
    lights[0]->setColor({1.0, 1.0, 1.0});
    lights[0]->setAmbientIntensity(0.0);
    addChild(lights[0]);
}


std::array<std::shared_ptr<Light>, 1> Car::getLights() const
{
    return lights;
}


void Car::update(float timeInterval)
{
    if(isAccelerating) {
        speed += kAcceleration;

        if(speed > kMaxSpeed)
            speed = kMaxSpeed;
    } else {
        if(speed > 0.0) {
            speed -= kSlowdownSpeed;

            if(speed < 0.0)
                speed = 0.0;
        } else if(speed < 0.0) {
            speed += kSlowdownSpeed;

            if(speed > 0.0)
                speed = 0.0;
        }
    }

    if(isTurningLeft) {
        wheelsTurn -= kWheelsTurnSpeed;
        if(wheelsTurn < -kMaxWheelsTurn)
            wheelsTurn = -kMaxWheelsTurn;
    } else if(isTurningRight) {
        wheelsTurn += kWheelsTurnSpeed;
        if(wheelsTurn > kMaxWheelsTurn)
            wheelsTurn = kMaxWheelsTurn;
    } else {
        if(wheelsTurn > 0.0) {
            wheelsTurn -= kWheelsTurnSpeed;
            if(wheelsTurn < 0.0)
                wheelsTurn = 0.0;
        } else if(wheelsTurn < 0.0) {
            wheelsTurn += kWheelsTurnSpeed;
            if(wheelsTurn > 0.0)
                wheelsTurn = 0.0;
        }
    }

    wheels[0]->rotation[1] = wheelsTurn*3;
    wheels[1]->rotation[1] = wheelsTurn*3;

    wheels[0]->rotation[0] += speed * 5;
    wheels[1]->rotation[0] += speed * 5;
    wheels[2]->rotation[0] += speed * 5;
    wheels[3]->rotation[0] += speed * 5;

    if(speed > 0.0) {
        rotation[1] += wheelsTurn;
    }

    GLfloat angleInRadians = (M_PI * rotation[1])/180.0;
    position[0] += speed * sin(angleInRadians);
    position[2] += speed * cos(angleInRadians);

    // Lights
    //lights[0]->setWorldTarget(lights[0]->position + Vector3{0.0, 0.0, 1.0});

    Instance3D::update(timeInterval);
}
