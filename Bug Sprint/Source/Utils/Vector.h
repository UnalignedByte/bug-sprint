//
//  Vector.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef VECTOR_H
#define VECTOR_H

template<int SIZE = 3>
class Vector
{
public:
    Vector();
    Vector(double initialValue);

    Vector<SIZE> operator+(const Vector<SIZE> &rhs);
    Vector<SIZE> operator*(double rhs);
    Vector<SIZE> operator/(double rhs);

    double m[SIZE];
};

#include "Vector.cpp"

#endif
