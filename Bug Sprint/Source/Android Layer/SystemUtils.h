//
// Created by Rafal Grodzinski on 04/11/2016.
//

#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#include <android_native_app_glue.h>
#include <string>

#include "FileBuffer.h"


struct ImageData
{
    unsigned char *rgbaImageData = nullptr;
    int width = 0;
    int height = 0;
};

class SystemUtils
{
public:
    static android_app *app;

public:
    static std::string pathForFileName(const std::string &fileName);
    static FileBuffer bufferForFileName(const std::string &fileName);
    static ImageData imageDataForFileName(const std::string &fileName);
};


#endif
