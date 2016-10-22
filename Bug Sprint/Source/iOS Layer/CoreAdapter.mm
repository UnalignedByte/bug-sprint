//
//  CoreAdapter.m
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#import "CoreAdapter.h"

#import "Core.h"

#import <string>

using namespace std;


@interface CoreAdapter()

@property (nonatomic, assign) Core *core;

@end


@implementation CoreAdapter

- (instancetype)initWithSize:(CGSize)size
{
    self = [super init];
    if(self == nil) return nil;

    try {
        self.core = new Core(double(size.width), double(size.height));
    } catch(string exception) {
        [self handleExceptionMessage:exception];
    }

    return self;
}


- (void)dealloc
{
    delete self.core;
}


- (void)update:(NSTimeInterval)timeInterval
{
    try {
        self.core->update(timeInterval);
    } catch(string exception) {
        [self handleExceptionMessage:exception];
    }
}


- (void)draw
{
    try {
        self.core->draw();
    } catch(string exception) {
        [self handleExceptionMessage:exception];
    }
}


- (void)handleExceptionMessage:(string)exception
{
    NSString *error = [NSString stringWithUTF8String:exception.c_str()];
    NSLog(@"!!! Exception Thrown !!!\n%@", error);
    abort();
}

@end
