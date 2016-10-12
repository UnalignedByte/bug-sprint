//
//  Instance.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 11/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef INSTANCE_H
#define INSTANCE_H

class Instance
{
public:
    virtual void update(double timeInterval) = 0;
    virtual void draw() = 0;
};

#endif
