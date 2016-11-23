//
//  Color.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Color.h"

#include <string>
#include <iostream>

using namespace std;


Color::Color() :
    data{0.0, 0.0, 0.0, 1.0}
{
}


Color::Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) :
    data{red, green, blue, alpha}
{
}


const GLfloat &Color::operator[](int index) const
{
    if(index < 0 || index >= 4)
        throw string("Index out of bounds");

    return data[index];
}


GLfloat &Color::operator[](int index)
{
    if(index < 0 || index >= 4)
        throw string("Index out of bounds");

    return data[index];
}
