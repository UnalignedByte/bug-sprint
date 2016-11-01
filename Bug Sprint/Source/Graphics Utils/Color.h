//
//  Color.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef COLOR_H
#define COLOR_H

#ifdef ANDROID
#include <GLES3/gl3.h>
#else
#include <OpenGLES/ES3/gl.h>
#endif


class Color
{
public:
    Color();
    Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0);

    const GLfloat &operator[](int index) const;
    GLfloat &operator[](int index);

private:
    GLfloat data[4];
};

#endif
