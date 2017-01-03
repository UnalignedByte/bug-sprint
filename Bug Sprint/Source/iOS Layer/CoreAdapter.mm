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

    // Remove events
    self.currentInput->touches.clear();
    /*vector<int> touchIdsToRemove;

    for(auto touchIt : self.currentInput->touches)
        if(touchIt.second.state == Input::Touch::StateUp || touchIt.second.state == Input::Touch::StateCanceled) {
            touchIdsToRemove.push_back(touchIt.first);
        }

    for(int touchId : touchIdsToRemove)
        self.currentInput->touches.erase(touchId);*/
}


- (void)draw
{
    try {
        self.core->draw();
    } catch(string exception) {
        [self handleExceptionMessage:exception];
    }
}


- (void)touchDownWithId:(NSInteger)touchId x:(NSInteger)x y:(NSInteger)y
{
    SystemUtils::Point pos = SystemUtils::positionForViewPosition(int(x), int(y));
    Input::Touch touch;
    touch.state = Input::Touch::StateDown;
    touch.downX = touch.x = pos.x;
    touch.downY = touch.y = pos.y;

    self.currentInput->touches[(int)touchId] = touch;
}


- (void)touchUpWithId:(NSInteger)touchId x:(NSInteger)x y:(NSInteger)y
{
    SystemUtils::Point pos = SystemUtils::positionForViewPosition(int(x), int(y));
    Input::Touch touch;
    touch.state = Input::Touch::StateUp;
    touch.x = pos.x;
    touch.y = pos.y;

    self.currentInput->touches[(int)touchId] = touch;
}


- (void)touchMoveWithId:(NSInteger)touchId x:(NSInteger)x y:(NSInteger)y
{
    // Is there a pending touch down event?
    if(self.currentInput->touches[(int)touchId].state == Input::Touch::StateDown)
        return;

    SystemUtils::Point pos = SystemUtils::positionForViewPosition(int(x), int(y));
    Input::Touch touch;
    touch.state = Input::Touch::StateMoved;
    touch.x = pos.x;
    touch.y = pos.y;

    self.currentInput->touches[(int)touchId] = touch;
}


- (void)touchCancelWithId:(NSInteger)touchId
{
    Input::Touch touch;
    touch.state = Input::Touch::StateCanceled;

    self.currentInput->touches[(int)touchId] = touch;
}


- (void)handleExceptionMessage:(string)exception
{
    NSString *error = [NSString stringWithUTF8String:exception.c_str()];
    NSLog(@"!!! Exception Thrown !!!\n%@", error);
    abort();
}

@end
