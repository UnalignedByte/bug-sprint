//
//  Image.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 07/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Image.h"

#include "SystemUtils.h"

using namespace std;


Image::Image(const std::string &fileName)
{
    SystemUtils::ImageData imageData = SystemUtils::imageDataForFileName(fileName);
    if(imageData.rgbaImageData == nullptr)
        throw string("Could not load image " + fileName);

    width = imageData.width;
    height = imageData.height;
    rgbaData = unique_ptr<GLubyte>(imageData.rgbaImageData);
}


Image::Image(const std::string &text, const std::string &fontFileName, GLfloat fontSize, const Color &fontColor)
{
    SystemUtils::ImageData imageData = SystemUtils::imageDataForText(text, fontFileName, fontSize, fontColor[0], fontColor[1], fontColor[2]);
    if(imageData.rgbaImageData == nullptr)
        throw string("Could not render text \"" + text + "\"");

    width = imageData.width;
    height = imageData.height;
    rgbaData = unique_ptr<GLubyte>(imageData.rgbaImageData);
}


Image::Image(const Image &that)
{
    width = that.width;
    height = that.height;

    size_t bytesCount = width * height * 4 * sizeof(GLubyte);
    GLubyte *data = (GLubyte *)malloc(bytesCount);
    memcpy(data, that.getData(), bytesCount);

    rgbaData = unique_ptr<GLubyte>(data);
}


Image &Image::operator=(Image &that)
{
    width = that.width;
    height = that.height;

    size_t bytesCount = width * height * 4 * sizeof(GLubyte);
    GLubyte *data = (GLubyte *)malloc(bytesCount);
    memcpy(data, that.getData(), bytesCount);

    rgbaData = unique_ptr<GLubyte>(data);

    return *this;
}


Image::Image(Image &&that)
{
    width = that.width;
    that.width = 0;
    height = that.height;
    that.height = 0;
    rgbaData = move(that.rgbaData);
    that.rgbaData = nullptr;
}


Image &Image::operator=(Image &&that)
{
    width = that.width;
    that.width = 0;
    height = that.height;
    that.height = 0;
    rgbaData = move(that.rgbaData);
    that.rgbaData = nullptr;

    return *this;
}


GLint Image::getWidth() const
{
    return width;
}


GLint Image::getHeight() const
{
    return height;
}


GLubyte *Image::getData() const
{
    return rgbaData.get();
}

