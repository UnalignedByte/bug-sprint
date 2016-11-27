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
#import "SystemUtils.h"

using namespace std;


@interface CoreAdapter()

@property (nonatomic, assign) Core *core;
@property (nonatomic, assign) Input *currentInput;

@end


@implementation CoreAdapter

- (instancetype)initWithViewSize:(CGSize)viewSize
{
    self = [super init];
    if(self == nil) return nil;

    try {
        self.currentInput = new Input;

        SystemUtils::viewWidth = int(viewSize.width);
        SystemUtils::viewHeight = int(viewSize.height);

        self.core = new Core(int(viewSize.width), int(viewSize.height));
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

    SystemUtils::Point pos = SystemUtils::positionForViewPosition(int(x), int(y));
    self.currentInput->downX = self.currentInput->x = pos.x;
    self.currentInput->downY = self.currentInput->y = pos.y;
}


- (void)touchUpAtX:(NSInteger)x y:(NSInteger)y
{
    self.currentInput->state = Input::StateUp;

    SystemUtils::Point pos = SystemUtils::positionForViewPosition(int(x), int(y));
    self.currentInput->x = pos.x;
    self.currentInput->y = pos.y;
}


- (void)touchMoveAtX:(NSInteger)x y:(NSInteger)y
{
    self.currentInput->state = Input::StateMoved;

    SystemUtils::Point pos = SystemUtils::positionForViewPosition(int(x), int(y));
    self.currentInput->x = pos.x;
    self.currentInput->y = pos.y;
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
