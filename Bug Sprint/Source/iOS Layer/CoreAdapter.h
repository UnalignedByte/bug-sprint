//
//  CoreAdapter.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 12/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CoreAdapter: NSObject

- (instancetype)initWithViewSize:(CGSize)size;

- (void)update:(NSTimeInterval)timeInterval;
- (void)draw;

- (void)touchDownWithId:(NSInteger)touchId x:(NSInteger)x y:(NSInteger)y;
- (void)touchUpWithId:(NSInteger)touchId x:(NSInteger)x y:(NSInteger)y;
- (void)touchMoveWithId:(NSInteger)touchId x:(NSInteger)x y:(NSInteger)y;
- (void)touchCancelWithId:(NSInteger)touchId;

@end
