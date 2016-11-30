//
//  ImageTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 30/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "Image.h"

using namespace std;


TEST(Image, RuleOfFive)
{
    Image img("mario.png");

    // Copy constructor
    Image copy0(img);
    ASSERT_EQ(copy0.getWidth(), img.getWidth());
    ASSERT_EQ(copy0.getHeight(), img.getHeight());
    ASSERT_NE(copy0.getData(), nullptr);
    ASSERT_NE(copy0.getData(), img.getData());

    // Copy assignment
    Image copy1("goose.jpg");
    copy1 = img;
    ASSERT_EQ(copy1.getWidth(), img.getWidth());
    ASSERT_EQ(copy1.getHeight(), img.getHeight());
    ASSERT_NE(copy1.getData(), nullptr);
    ASSERT_NE(copy1.getData(), img.getData());
}
