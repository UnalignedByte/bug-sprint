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

    Vector<SIZE> operator+(const Vector<SIZE> &rhs) const;
    Vector<SIZE> operator*(double rhs) const;
    Vector<SIZE> operator/(double rhs) const;

    double length() const;
    Vector<SIZE> normalized() const;
    double dot(const Vector<SIZE> &rhs) const;
    Vector<3> cross(const Vector<3> &rhs) const;

    // MARK: - Data
    double m[SIZE];
};

#include "Vector.cpp"

#endif
