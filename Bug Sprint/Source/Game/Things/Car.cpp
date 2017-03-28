//
//  Car.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Car.h"

#include <iostream>
#include <sstream>
#include "SystemUtils.h"

using namespace std;


static GLfloat kMaxSpeed = 0.2;
static GLfloat kAcceleration = kMaxSpeed * 0.02;
static GLfloat kSlowdownSpeed = kMaxSpeed * 0.05;
static GLfloat kMaxWheelsTurn = 10.0;
static GLfloat kWheelsTurnSpeed = kMaxWheelsTurn * 0.05;
static GLfloat kMaxTilt = 5.0;
static GLfloat kTiltSpeed = kMaxTilt * 0.04;


Car::Car(GLint viewWidth, GLint viewHeight) :
    viewWidth(viewWidth), viewHeight(viewHeight)
{
    body = make_shared<Drawable>("Game/Things/car_body.obj");
    body->getModel()->setColor(Color(1.0, 0.0, 0.0));
    body->getModel()->setDiffuseIntensity(1.0);
    body->getModel()->setSpecularIntensity(2.0);
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
    lights[0] = make_shared<Light>(0, 10.0, 10.0);
    lights[0]->setDirection({-0.1, 0.0, 1.0});
    lights[0]->position = {-0.5, -0.5, 1.0};
    lights[0]->setColor({1.0, 1.0, 1.0});
    lights[0]->setAmbientIntensity(0.0);
    addChild(lights[0]);

    lights[1] = make_shared<Light>(0, 10.0, 10.0);
    lights[1]->setDirection({0.1, 0.0, 1.0});
    lights[1]->position = {0.5, -0.5, 1.0};
    lights[1]->setColor({1.0, 1.0, 1.0});
    lights[1]->setAmbientIntensity(0.0);
    addChild(lights[1]);
}


std::array<std::shared_ptr<Light>, 2> Car::getLights() const
{
    return lights;
}


bool Car::getShouldCastShadow(shared_ptr<Light> light) const
{
    for(shared_ptr<Light> carLight : lights) {
        if(carLight == light)
            return false;
    }

    return true;
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

    wheels[0]->rotation[1] = wheelsTurn;
    wheels[1]->rotation[1] = wheelsTurn;

    wheels[0]->rotation[0] += speed * 20;
    wheels[1]->rotation[0] += speed * 20;
    wheels[2]->rotation[0] += speed * 20;
    wheels[3]->rotation[0] += speed * 20;

    //if(speed > 0.0) {
        rotation[1] += wheelsTurn * speed;
    //}

    // Tilt
    if (isAccelerating && speed < kMaxSpeed) {
        tiltAcceleration += kTiltSpeed;
        if(tiltAcceleration > kMaxTilt)
            tiltAcceleration = kMaxTilt;
    } else {
        tiltAcceleration -= kTiltSpeed;
        if(tiltAcceleration < 0.0)
        tiltAcceleration = 0.0;
    }

    if(isTurningLeft) {
        tiltTurn -= kTiltSpeed;
        if(tiltTurn < -kMaxTilt)
            tiltTurn = -kMaxTilt;
    } else if(isTurningRight) {
        tiltTurn += kTiltSpeed;
        if(tiltTurn > kMaxTilt)
            tiltTurn = kMaxTilt;
    } else if(tiltTurn > 0.0 ) {
        tiltTurn -= kTiltSpeed;
        if(tiltTurn < 0.0)
            tiltTurn = 0.0;
    } else if(tiltTurn < 0.0) {
        tiltTurn += kTiltSpeed;
        if(tiltTurn > 0.0)
            tiltTurn = 0.0;
    }

    body->rotation[0] = -tiltAcceleration;
    body->rotation[2] = tiltTurn;

    GLfloat angleInRadians = (M_PI * rotation[1])/180.0;
    position[0] += speed * sin(angleInRadians);
    position[2] += speed * cos(angleInRadians);

    Instance3D::update(timeInterval);
}
