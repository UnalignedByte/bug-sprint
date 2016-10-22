//
//  Vector.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Vector.h"

#include <string>
#include <cmath>


template<int SIZE>
Vector<SIZE>::Vector() : Vector(0.0)
{
    if(SIZE <= 0)
        throw std::string("Invalid size");
}


template<int SIZE>
Vector<SIZE>::Vector(GLfloat initialValue)
{
    if(SIZE <= 0)
        throw std::string("Invalid size");

    for(int i=0; i<SIZE; i++)
        data[i] = initialValue;
}


template<int SIZE>
Vector<SIZE>::Vector(std::initializer_list<GLfloat> values)
{
    if(SIZE <= 0)
        throw std::string("Invalid size");

    if(values.size() != SIZE)
        throw std::string("Invalid initializer list");

    int i = 0;
    for(auto value = values.begin(); value != values.end(); value++) {
        data[i] = *value;
        i++;
    }
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator+(const Vector<SIZE> &rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result[i] = data[i] + rhs[i];

    return result;
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator-(const Vector<SIZE> &rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result[i] = data[i] - rhs[i];

    return result;
}

template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator*(GLfloat rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result[i] = data[i] * rhs;

    return result;
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::operator/(GLfloat rhs) const
{
    Vector<SIZE> result;
    for(int i=0; i<SIZE; i++)
        result[i] = data[i] / rhs;

    return result;
}


template<int SIZE>
const GLfloat &Vector<SIZE>::operator[](int index) const
{
    if(index < 0 || index >= SIZE)
        throw std::string("Index out of bounds");

    return data[index];
}


template<int SIZE>
GLfloat &Vector<SIZE>::operator[](int index)
{
    if(index < 0 || index >= SIZE)
        throw std::string("Index out of bounds");

    return data[index];
}


template<int SIZE>
GLfloat Vector<SIZE>::length() const
{
    GLfloat sum = 0;
    for(int i=0; i<SIZE; i++)
        sum += data[i] * data[i];

    return sqrt(sum);
}


template<int SIZE>
Vector<SIZE> Vector<SIZE>::normalized() const
{
    Vector<SIZE> result;

    GLfloat vecLength = length();
    for(int i=0; i<SIZE; i++)
        result[i] = data[i]/vecLength;

    return result;
}


template<int SIZE>
GLfloat Vector<SIZE>::dot(const Vector<SIZE> &rhs) const
{
    GLfloat sum = 0.0;
    for(int i=0; i<SIZE; i++)
        sum += data[i] * rhs[i];

    return sum;
}


template<int SIZE>
Vector<3> Vector<SIZE>::cross(const Vector<3> &rhs) const
{
    if(SIZE != 3)
        throw std::string("Invalid size");

    Vector<3> result;

    result[0] = data[1] * rhs[2] - data[2] * rhs[1]; // y1 * z2 - z1 * y2
    result[1] = data[2] * rhs[0] - data[0] * rhs[2]; // z1 * x2 - x1 * z2
    result[2] = data[0] * rhs[1] - data[1] * rhs[0]; // x1 * y2 - y1 * x2

    return result;
}
