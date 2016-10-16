//
//  ColorTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "Color.h"


TEST(Color, Create)
{
    Color c1;
    ASSERT_DOUBLE_EQ(c1[0], 0.0);
    ASSERT_DOUBLE_EQ(c1[1], 0.0);
    ASSERT_DOUBLE_EQ(c1[2], 0.0);
    ASSERT_DOUBLE_EQ(c1[3], 1.0);

    Color c2(1.0, 0.5, 0.0, 1.0);
    ASSERT_DOUBLE_EQ(c2[0], 1.0);
    ASSERT_DOUBLE_EQ(c2[1], 0.5);
    ASSERT_DOUBLE_EQ(c2[2], 0.0);
    ASSERT_DOUBLE_EQ(c2[3], 1.0);
    ASSERT_THROW(c2[4], std::string);
}
