//
//  Matrix.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 15/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <OpenGLES/ES3/gl.h>

#include "Vector.h"

template<int SIZE>
class Matrix
{
public:
    Matrix();
    Matrix(GLfloat initialValue);
    Matrix(std::initializer_list<Vector<SIZE>> values);

    Matrix<SIZE> operator*(GLfloat rhs) const;
    Matrix<SIZE> operator*(const Matrix<SIZE> &rhs) const;

    const Vector<SIZE> &operator[](int index) const;
    Vector<SIZE> &operator[](int index);

    static Matrix<4> translation(GLfloat x, GLfloat y, GLfloat z);

private:
    Vector<SIZE> data[SIZE];
};

using Matrix3 = Matrix<3>;
using Matrix4 = Matrix<4>;

#include "Matrix.cpp"

#endif
