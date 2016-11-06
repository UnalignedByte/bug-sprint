//
// Created by Rafal Grodzinski on 04/11/2016.
//

#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#include <android_native_app_glue.h>
#include <string>

#include "FileBuffer.h"


class SystemUtils
{
public:
    static android_app *app;

    static std::string pathForFileName(const std::string &fileName);
    static FileBuffer bufferForFileName(const std::string &fileName);
};


#endif
