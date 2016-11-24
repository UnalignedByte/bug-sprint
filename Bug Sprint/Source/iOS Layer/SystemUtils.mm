//
//  Utils.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "SystemUtils.h"

#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>

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


ImageData SystemUtils::imageDataForText(const std::string &text, const std::string &fontFileName, float fontSize, float red, float green, float blue)
{
    ImageData imageData;

    NSString *textString = [NSString stringWithUTF8String:text.c_str()];

    string fontName = fontNameForFontFileName(fontFileName);
    NSString *fontNameString = [NSString stringWithUTF8String:fontName.c_str()];
    UIFont *font = [UIFont fontWithName:fontNameString size:fontSize * getScale()];
    if(font == nil)
        return imageData;

    NSDictionary *stringAttributes = @{NSFontAttributeName : font,
                                       NSForegroundColorAttributeName : [UIColor colorWithRed:red green:green blue:blue alpha:1.0]};
    NSAttributedString *attributedString = [[NSAttributedString alloc] initWithString:textString attributes:stringAttributes];

    CGSize stringSize = [attributedString size];
    imageData.width = stringSize.width;
    imageData.height = stringSize.height;

    imageData.rgbaImageData = (unsigned char *)calloc(imageData.width * imageData.height * 4, sizeof(unsigned char));

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGContextRef ctx = CGBitmapContextCreate(imageData.rgbaImageData, imageData.width, imageData.height,
        8, 4 * imageData.width, colorSpaceRef, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpaceRef);

    UIGraphicsPushContext(ctx);
    CGContextTranslateCTM(ctx, 0.0, imageData.height);
    CGContextScaleCTM(ctx, 1.0, -1.0);

    [attributedString drawAtPoint:CGPointZero];

    UIGraphicsPopContext();

    CGContextRelease(ctx);


    return imageData;
}


float SystemUtils::getScale()
{
    return [UIScreen mainScreen].scale;
}


string SystemUtils::fontNameForFontFileName(const std::string &fontFileName)
{
    NSString *fontFileNameString = [NSString stringWithUTF8String:fontFileName.c_str()];

    static NSMutableDictionary *namesDict = [NSMutableDictionary dictionary];

    // If font is already registered, return the name
    NSString *fontNameString = namesDict[fontFileNameString];
    if(fontNameString != nil)
        return [fontNameString UTF8String];

    NSString *fontFilePath = [[NSBundle mainBundle] pathForResource:fontFileNameString ofType:nil];
    if(fontFilePath == nil)
        return "";

    CGDataProviderRef fontDataProvider = CGDataProviderCreateWithFilename([fontFilePath UTF8String]);
    CGFontRef font = CGFontCreateWithDataProvider(fontDataProvider);
    CGDataProviderRelease(fontDataProvider);
    fontNameString = (__bridge NSString *)CGFontCopyPostScriptName(font);

    CFErrorRef error;
    CTFontManagerRegisterGraphicsFont(font, &error);
    CGFontRelease(font);

    namesDict[fontFileNameString] = fontNameString;

    return [fontNameString UTF8String];
}
