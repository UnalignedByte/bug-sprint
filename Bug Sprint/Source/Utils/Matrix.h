//
//  Matrix.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 15/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

#include <initializer_list>


template<int SIZE>
class Matrix
{
public:
    Matrix();
    Matrix(double initialValue);
    Matrix(std::initializer_list<Vector<SIZE>> values);

    Vector<SIZE> &operator[](int index) const;
    Vector<SIZE> &operator[](int index);

private:
    Vector<SIZE> data[SIZE];
};

#include "Matrix.cpp"

#endif
