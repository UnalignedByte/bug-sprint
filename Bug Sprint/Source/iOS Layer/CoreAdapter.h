//
//  CoreAdapter.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CoreAdapter: NSObject

- (instancetype)initWithSize:(CGSize)size;

- (void)update:(NSTimeInterval)timeInterval;
- (void)draw;

- (void)touchDownAtX:(NSInteger)x y:(NSInteger)y;
- (void)touchUpAtX:(NSInteger)x y:(NSInteger)y;
- (void)touchMoveAtX:(NSInteger)x y:(NSInteger)y;
- (void)touchCancel;

@end
