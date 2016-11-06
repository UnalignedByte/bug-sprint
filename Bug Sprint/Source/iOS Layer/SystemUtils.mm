//
//  Utils.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "SystemUtils.h"

#import <Foundation/Foundation.h>

using namespace std;


string SystemUtils::pathForFileName(const string &fileName)
{
    NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];

    for(NSBundle *bundle in [NSBundle allBundles]) {
        NSString *filePathString = [bundle pathForResource:fileNameString ofType:nil];

        if(filePathString.length > 0)
            return string(filePathString.UTF8String);
    }

    return "";
}


FileBuffer SystemUtils::bufferForFileName(const std::string &fileName)
{
    NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];

    NSData *fileData = [NSData dataWithContentsOfFile:fileNameString];
    FileBuffer fileBuffer(const_cast<void *>(fileData.bytes), fileData.length);

    return fileBuffer;
}
