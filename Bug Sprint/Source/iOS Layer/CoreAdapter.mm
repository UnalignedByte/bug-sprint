//
//  CoreAdapter.m
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#import "CoreAdapter.h"

#import "Core.h"


@interface CoreAdapter()

@property (nonatomic, assign) Core *core;

@end


@implementation CoreAdapter

- (instancetype)initWithSize:(CGSize)size
{
    self = [super init];
    if(self == nil) return nil;

    self.core = new Core(double(size.width), double(size.height));

    return self;
}


- (void)dealloc
{
    delete self.core;
}


- (void)update:(NSTimeInterval)timeInterval
{
    self.core->update(timeInterval);
}


- (void)draw
{
    self.core->draw();
}

@end
