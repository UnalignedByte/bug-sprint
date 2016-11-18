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
#include "OpenGLES.h"

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

    GLfloat *getData();

    static Matrix<4> translation(GLfloat x, GLfloat y, GLfloat z);
    static Matrix<4> scale(GLfloat x, GLfloat y, GLfloat z);
    static Matrix<4> xRotation(GLfloat angle);
    static Matrix<4> yRotation(GLfloat angle);
    static Matrix<4> zRotation(GLfloat angle);
    static Matrix<4> ortographicProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
    static Matrix<4> perspectiveProjection(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
    static Matrix<4> lookAt(Vector3 eye, Vector3 target);

private:
    GLfloat rawData[SIZE*SIZE];
    Vector<SIZE> data[SIZE];
};

using Matrix3 = Matrix<3>;
using Matrix4 = Matrix<4>;

#include "Matrix.cpp"

#endif
