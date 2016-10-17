//
//  Matrix.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 15/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Matrix.h"

#include <string>
#include <cmath>

using namespace std;


template<int SIZE>
Matrix<SIZE>::Matrix()
{
    if(SIZE <= 0)
        throw string("Invalid size");
}


template<int SIZE>
Matrix<SIZE>::Matrix(GLfloat initialValue)
{
    if(SIZE <= 0)
        throw string("Invalid size");

    for(int i=0; i<SIZE; i++)
        data[i] = Vector<SIZE>(initialValue);
}


template<int SIZE>
Matrix<SIZE>::Matrix(initializer_list<Vector<SIZE>> values)
{
    if(SIZE <= 0)
        throw string("Invalid size");

    if(values.size() != SIZE)
        throw string("Invalid initializer list");

    int i=0;
    for(auto value = values.begin(); value != values.end(); value++) {
        data[i] = *value;
        i++;
    }
}


template<int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator*(GLfloat rhs) const
{
    Matrix<SIZE> result;

    for(int i=0; i<SIZE; i++)
        result[i] = data[i] * rhs;

    return result;
}


template<int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator*(const Matrix<SIZE> &rhs) const
{
    Matrix<SIZE> result;

    for(int y=0; y<SIZE; y++)
        for(int x=0; x<SIZE; x++) {
            GLfloat sum = 0.0;
            for(int i=0; i<SIZE; i++) {
                sum += data[y][i] * rhs[i][x];
            }
            result[y][x] = sum;
        }

    return result;
}


template<int SIZE>
const Vector<SIZE> &Matrix<SIZE>::operator[](int index) const
{
    if(index < 0 || index >= SIZE)
        throw string("Index out of bounds");

    return data[index];
}


template<int SIZE>
Vector<SIZE> &Matrix<SIZE>::operator[](int index)
{
    if(index < 0 || index >= SIZE)
        throw string("Index out of bounds");

    return data[index];
}
