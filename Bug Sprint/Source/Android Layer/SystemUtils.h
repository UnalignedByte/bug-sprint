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
    struct ImageData
    {
        unsigned char *rgbaImageData = nullptr;
        int width = 0;
        int height = 0;
    };

    struct Point
    {
        float x;
        float y;
    };

public:
    static android_app *app;
    static int viewWidth;
    static int viewHeight;

public:
    static std::string pathForFileName(const std::string &fileName);
    static FileBuffer bufferForFileName(const std::string &fileName);
    static ImageData imageDataForFileName(const std::string &fileName);
    static ImageData imageDataForText(const std::string &text, const std::string &fontFileName,
        float fontSize, float red, float green, float blue);
    static float getScale();
    static Point sizeForViewSize(int width, int height);
    static Point positionForViewPosition(int x, int y);

private:
    static jobject getAssetsManager();
    static jobject getResources();
};


#endif
