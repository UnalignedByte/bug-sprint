//
//  Vector.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Vector.h"


template<int SIZE>
Vector<SIZE>::Vector() : Vector(0.0)
{
}


template<int SIZE>
Vector<SIZE>::Vector(double initialValue)
{
    for(int i=0; i<SIZE; i++)
        m[i] = initialValue;
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator+(const Vector<SIZE> &rhs)
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result.m[i] = m[i] + rhs.m[i];

    return result;
}
