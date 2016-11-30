//
//  Image.hpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 07/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include "OpenGLES.h"
#include "Color.h"


class Image
{
public:
    Image(const std::string &fileName);
    Image(const std::string &text, const std::string &fontFileName, GLfloat fontSize, const Color &fontColor);
    Image(const Image &that);
    Image &operator=(Image &that);
    Image(Image &&that);
    Image &operator=(Image &&that);

    GLint getWidth() const;
    GLint getHeight() const;
    GLubyte *getData() const;

private:
    GLint width;
    GLint height;
    std::unique_ptr<GLubyte> rgbaData;
};

#endif
