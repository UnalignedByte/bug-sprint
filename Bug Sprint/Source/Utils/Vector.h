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
#include <OpenGLES/ES3/gl.h>


template<int SIZE>
class Vector
{
public:
    Vector();
    Vector(GLfloat initialValue);
    Vector(std::initializer_list<GLfloat> values);

    Vector<SIZE> operator+(const Vector<SIZE> &rhs) const;
    Vector<SIZE> operator-(const Vector<SIZE> &rhs) const;
    Vector<SIZE> operator*(GLfloat rhs) const;
    Vector<SIZE> operator/(GLfloat rhs) const;

    const GLfloat &operator[](int index) const;
    GLfloat &operator[](int index);

    GLfloat length() const;
    Vector<SIZE> normalized() const;
    GLfloat dot(const Vector<SIZE> &rhs) const;
    Vector<3> cross(const Vector<3> &rhs) const;

private:
    GLfloat data[SIZE];
};

using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

#include "Vector.cpp"

#endif
