//
//  Utils.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

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
    static std::string pathForFileName(const std::string &fileName);
    static FileBuffer bufferForFileName(const std::string &fileName);
    static ImageData imageDataForFileName(const std::string &fileName);
    static ImageData imageDataForText(const std::string &text, const std::string &fontFileName, float fontSize, float red, float green, float blue);

    static float getScale();

protected:
    static std::string fontNameForFontFileName(const std::string &fontFileName);
};

#endif
