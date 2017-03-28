//
//  Bug.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 28/03/2017.
//  Copyright © 2017 UnalignedByte. All rights reserved.
//

#include "Bug.h"

#include <random>

using namespace std;

static float kMinActionDurationSpeed = 1.0;
static float kMaxActionDurationSpeed = 3.0;
static GLfloat kMinRotationSpeed = 15.0;
static GLfloat kMaxRotationSpeed = 90.0;
static GLfloat kMinMovementSpeed = 2.0;
static GLfloat kMaxMovementSpeed = 5.0;

Bug::Bug()
{
    bugBody = make_shared<Drawable>("Game/Things/bug_body.obj");
    addChild(bugBody);

    random_device generator;
    uniform_real_distribution<float> distribution(0.0, 360.0);
    rotation[1] = distribution(generator);
}


void Bug::update(float timeInterval)
{
    actionRemainingDuration -= timeInterval;
    if(actionRemainingDuration <= 0.0) {
        newActionDuration();
        newActionRotation();
        newActionMovement();
    } else {
        updateActionRotation(timeInterval);
        updateActionMovement(timeInterval);
    }

    Instance3D::update(timeInterval);
}


void Bug::newActionDuration()
{
    random_device generator;
    uniform_real_distribution<float> distribution(kMinActionDurationSpeed, kMaxActionDurationSpeed);
    actionRemainingDuration = distribution(generator);
}


void Bug::newActionRotation()
{
    random_device generator;
    uniform_real_distribution<GLfloat> distribution(kMinRotationSpeed, kMaxRotationSpeed);
    rotationSpeed = distribution(generator);

    if(rand() % 2 == 0) {
        rotationSpeed *= -1.0;
    }
}


void Bug::newActionMovement()
{
    random_device generator;
    uniform_real_distribution<GLfloat> distribution(kMinMovementSpeed, kMaxMovementSpeed);
    movementSpeed = distribution(generator);
}


void Bug::updateActionRotation(float timeInterval)
{
    rotation[1] += rotationSpeed * timeInterval;
}


void Bug::updateActionMovement(float timeInterval)
{
    GLfloat angleInRadians = (M_PI * rotation[1])/180.0;
    position[0] += sin(angleInRadians) * movementSpeed * timeInterval;
    position[2] += cos(angleInRadians) * movementSpeed * timeInterval;
}
