//
//  CoreAdapter.m
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#import "CoreAdapter.h"

#import <string>

#import "Core.h"
#import "Types.h"

using namespace std;


@interface CoreAdapter()

@property (nonatomic, assign) Core *core;

@property (nonatomic, assign) NSInteger width;
@property (nonatomic, assign) NSInteger height;
@property (nonatomic, assign) Input *currentInput;

@end


@implementation CoreAdapter

- (instancetype)initWithSize:(CGSize)size
{
    self = [super init];
    if(self == nil) return nil;

    try {
        self.width = size.width;
        self.height = size.height;
        self.currentInput = new Input;

        self.core = new Core(double(size.width), double(size.height));
    } catch(string exception) {
        [self handleExceptionMessage:exception];
    }

    return self;
}


- (void)dealloc
{
    delete self.core;
    delete self.currentInput;
}


- (void)update:(NSTimeInterval)timeInterval
{
    try {
        self.core->update(timeInterval, *self.currentInput);
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


- (void)touchDownAtX:(NSInteger)x y:(NSInteger)y
{
    self.currentInput->state = Input::StateDown;

    double xPos = double(x) / double(self.width);
    double yPos = double(y) / double(self.height);
    self.currentInput->downX = self.currentInput->x = xPos;
    self.currentInput->downY = self.currentInput->y = yPos;
}


- (void)touchUpAtX:(NSInteger)x y:(NSInteger)y
{
    self.currentInput->state = Input::StateUp;

    double xPos = double(x) / double(self.width);
    double yPos = double(y) / double(self.height);
    self.currentInput->x = xPos;
    self.currentInput->y = yPos;
}


- (void)touchMoveAtX:(NSInteger)x y:(NSInteger)y
{
    self.currentInput->state = Input::StateMoved;

    double xPos = double(x) / double(self.width);
    double yPos = double(y) / double(self.height);
    self.currentInput->x = xPos;
    self.currentInput->y = yPos;
}


- (void)touchCancel
{
    self.currentInput->state = Input::StateCanceled;
}


- (void)handleExceptionMessage:(string)exception
{
    NSString *error = [NSString stringWithUTF8String:exception.c_str()];
    NSLog(@"!!! Exception Thrown !!!\n%@", error);
    abort();
}

@end
