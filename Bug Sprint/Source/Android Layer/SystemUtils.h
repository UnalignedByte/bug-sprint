//
// Created by Rafal Grodzinski on 04/11/2016.
//

#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#include <string>
#include <android_native_app_glue.h>


class SystemUtils
{
public:
    static android_app *app;

    static std::string pathForFileName(const std::string &fileName);
};


#endif
