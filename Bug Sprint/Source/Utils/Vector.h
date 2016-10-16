//
//  Vector.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>


template<int SIZE>
class Vector
{
public:
    Vector();
    Vector(double initialValue);
    Vector(std::initializer_list<double> values);

    Vector<SIZE> operator+(const Vector<SIZE> &rhs) const;
    Vector<SIZE> operator-(const Vector<SIZE> &rhs) const;
    Vector<SIZE> operator*(double rhs) const;
    Vector<SIZE> operator/(double rhs) const;

    const double &operator[](int index) const;
    double &operator[](int index);

    double length() const;
    Vector<SIZE> normalized() const;
    double dot(const Vector<SIZE> &rhs) const;
    Vector<3> cross(const Vector<3> &rhs) const;

private:
    double data[SIZE];
};

#include "Vector.cpp"

#endif
