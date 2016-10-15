//
//  Vector.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Vector.h"

#include <cmath>
#include <string>

using namespace std;


template<int SIZE>
Vector<SIZE>::Vector() : Vector(0.0)
{
    if(SIZE <= 0)
        throw string("Invalid vector size");
}


template<int SIZE>
Vector<SIZE>::Vector(double initialValue)
{
    if(SIZE <= 0)
        throw string("Invalid vector size");

    for(int i=0; i<SIZE; i++)
        m[i] = initialValue;
}


template<int SIZE>
Vector<SIZE>::Vector(initializer_list<double> values)
{
    if(SIZE <= 0)
        throw string("Invalid vector size");

    if(values.size() != SIZE)
        throw string("Invalid initializer list");

    int i = 0;
    for(auto value = values.begin(); value != values.end(); value++) {
        m[i] = *value;
        i++;
    }
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator+(const Vector<SIZE> &rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result.m[i] = m[i] + rhs.m[i];

    return result;
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator-(const Vector<SIZE> &rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result.m[i] = m[i] - rhs.m[i];

    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator*(double rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result.m[i] = m[i] * rhs;

    return result;
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator/(double rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result.m[i] = m[i] / rhs;

    return result;
}


template<int SIZE>
double Vector<SIZE>::length() const
{
    double sum = 0;
    for(int i=0; i<SIZE; i++)
        sum += m[i] * m[i];

    return sqrt(sum);
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::normalized() const
{
    Vector<SIZE> result;

    double vecLength = length();
    for(int i=0; i<SIZE; i++)
        result.m[i] = m[i]/vecLength;

    return result;
}


template<int SIZE>
double Vector<SIZE>::dot(const Vector<SIZE> &rhs) const
{
    double sum = 0.0;
    for(int i=0; i<SIZE; i++)
        sum += m[i] * rhs.m[i];

    return sum;
}


template<int SIZE>
Vector<3> Vector<SIZE>::cross(const Vector<3> &rhs) const
{
    if(SIZE != 3)
        throw string("Invalid vector size");

    Vector<3> result;

    result.m[0] = m[1] * rhs.m[2] - m[2] * rhs.m[1]; // y1 * z2 - z1 * y2
    result.m[1] = m[2] * rhs.m[0] - m[0] * rhs.m[2]; // z1 * x2 - x1 * z2
    result.m[2] = m[0] * rhs.m[1] - m[1] * rhs.m[0]; // x1 * y2 - y1 * x2

    return result;
}
