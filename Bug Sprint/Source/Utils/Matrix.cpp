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

    // Reset to identity
    for(int i=0; i<SIZE; i++)
        data[i][i] = 1.0;
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


template<int SIZE>
GLfloat *Matrix<SIZE>::getData()
{
    for(int y=0; y<SIZE; y++)
        for(int x=0; x<SIZE; x++) {
            rawData[y*SIZE + x] = data[y][x];
        }

    return rawData;
}


template<int SIZE>
Matrix<4> Matrix<SIZE>::translation(GLfloat x, GLfloat y, GLfloat z)
{
    Matrix<4> matrix;
    matrix[3][0] = x;
    matrix[3][1] = y;
    matrix[3][2] = z;

    return matrix;
}


template<int SIZE>
Matrix<4> Matrix<SIZE>::xRotation(GLfloat angle)
{
    GLfloat angleInRadians = (M_PI * angle)/180.0;

    Matrix<4> matrix;
    matrix[1][1] = cos(angleInRadians);
    matrix[1][2] = sin(angleInRadians);
    matrix[2][1] = -sin(angleInRadians);
    matrix[2][2] = cos(angleInRadians);

    return matrix;
}

template<int SIZE>
Matrix<4> Matrix<SIZE>::yRotation(GLfloat angle)
{
    GLfloat angleInRadians = (M_PI * angle)/180.0;

    Matrix<4> matrix;
    matrix[0][0] = cos(angleInRadians);
    matrix[0][2] = -sin(angleInRadians);
    matrix[2][0] = sin(angleInRadians);
    matrix[2][2] = cos(angleInRadians);

    return matrix;
}


template<int SIZE>
Matrix<4> Matrix<SIZE>::zRotation(GLfloat angle)
{
    GLfloat angleInRadians = (M_PI * angle)/180.0;

    Matrix<4> matrix;
    matrix[0][0] = cos(angleInRadians);
    matrix[0][1] = sin(angleInRadians);
    matrix[1][0] = -sin(angleInRadians);
    matrix[1][1] = cos(angleInRadians);

    return matrix;
}


template<int SIZE>
Matrix<4> Matrix<SIZE>::perspectiveProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
{
    Matrix<4> matrix;
    GLfloat top = near * tan(M_PI/180.0 * fov/2.0);
    GLfloat bottom = -top;
    GLfloat right = top * aspect;
    GLfloat left = -right;

    matrix[0][0] = (2 * near)/(right - left);
    matrix[0][2] = (right + left)/(right - left);

    matrix[1][1] = (2 * near)/(top - bottom);
    matrix[1][2] = (top + bottom)/(top - bottom);

    matrix[2][2] = -(far + near)/(far - near);
    matrix[2][3] = -(2 * far * near)/(far - near);

    matrix[3][2] = -1.0;

    return matrix;
}
