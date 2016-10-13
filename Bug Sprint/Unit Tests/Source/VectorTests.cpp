//
//  VectorTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>
#include "Vector.h"


TEST(Vector, CreateV3)
{
    Vector<3> v3;
    ASSERT_EQ(v3.m[0], 0.0);
    ASSERT_EQ(v3.m[1], 0.0);
    ASSERT_EQ(v3.m[2], 0.0);

    Vector<3> v3Initial(1.0);
    ASSERT_EQ(v3Initial.m[0], 1.0);
    ASSERT_EQ(v3Initial.m[1], 1.0);
    ASSERT_EQ(v3Initial.m[2], 1.0);
}


TEST(Vector, CreateV4)
{
    Vector<4> v4;
    ASSERT_EQ(v4.m[0], 0.0);
    ASSERT_EQ(v4.m[1], 0.0);
    ASSERT_EQ(v4.m[2], 0.0);
    ASSERT_EQ(v4.m[3], 0.0);

    Vector<4> v4Initial(1.0);
    ASSERT_EQ(v4Initial.m[0], 1.0);
    ASSERT_EQ(v4Initial.m[1], 1.0);
    ASSERT_EQ(v4Initial.m[2], 1.0);
    ASSERT_EQ(v4Initial.m[3], 1.0);
}


TEST(Vector, Addition)
{
    Vector<3> first(1.0);
    Vector<3> second(2.0);

    Vector<3> result = first + second;
    ASSERT_EQ(result.m[0], 3.0);
    ASSERT_EQ(result.m[1], 3.0);
    ASSERT_EQ(result.m[2], 3.0);
}


TEST(Vector, Multiply)
{
    Vector<3> vec(2.0);

    Vector<3> result = vec * 4.0;
    ASSERT_EQ(result.m[0], 8.0);
    ASSERT_EQ(result.m[1], 8.0);
    ASSERT_EQ(result.m[2], 8.0);
}


TEST(Vector, Divide)
{
    Vector<3> vec(8.0);

    Vector<3> result = vec / 4.0;
    ASSERT_EQ(result.m[0], 2.0);
    ASSERT_EQ(result.m[1], 2.0);
    ASSERT_EQ(result.m[2], 2.0);
}
