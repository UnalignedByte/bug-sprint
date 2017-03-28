//
//  Bug.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 28/03/2017.
//  Copyright © 2017 UnalignedByte. All rights reserved.
//

#ifndef BUG_H
#define BUG_H

#include "Drawable.h"


class Bug: public Drawable
{
public:
    Bug();

    void update(float timeInterval) override;

protected:
    std::shared_ptr<Drawable> bugBody;
    float actionRemainingDuration{0};
    GLfloat rotationSpeed;
    GLfloat movementSpeed;

    void newActionDuration();
    void newActionRotation();
    void newActionMovement();
    void updateActionRotation(float timeInterval);
    void updateActionMovement(float timeInterval);
};

#endif
