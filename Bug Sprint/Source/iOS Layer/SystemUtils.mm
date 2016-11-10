//
//  Utils.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "SystemUtils.h"

#import <UIKit/UIKit.h>

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


ImageData SystemUtils::imageDataForFileName(const string &fileName)
{
    ImageData imageData;

    NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
    UIImage *image = [UIImage imageNamed:fileNameString];
    if(image == nil)
        return imageData;

    CGImageRef imageRef = image.CGImage;
    imageData.width = int(CGImageGetWidth(imageRef));
    imageData.height = int(CGImageGetHeight(imageRef));
    imageData.rgbaImageData = (unsigned char *)calloc(imageData.width * imageData.height * 4, sizeof(unsigned char));

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGContextRef ctx = CGBitmapContextCreate(imageData.rgbaImageData, imageData.width, imageData.height,
                                             8, 4 * imageData.width,
                                             colorSpaceRef, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpaceRef);

    CGContextDrawImage(ctx, CGRectMake(0, 0, imageData.width, imageData.height), imageRef);
    CGContextRelease(ctx);

    return imageData;
}
