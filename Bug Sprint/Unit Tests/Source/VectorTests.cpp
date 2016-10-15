//
//  VectorTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>
#include "Vector.h"


TEST(Vector, CreateDefault)
{
    Vector<3> v3;
    ASSERT_DOUBLE_EQ(v3.m[0], 0.0);
    ASSERT_DOUBLE_EQ(v3.m[1], 0.0);
    ASSERT_DOUBLE_EQ(v3.m[2], 0.0);

    Vector<5> v5;
    ASSERT_DOUBLE_EQ(v5.m[0], 0.0);
    ASSERT_DOUBLE_EQ(v5.m[1], 0.0);
    ASSERT_DOUBLE_EQ(v5.m[2], 0.0);
    ASSERT_DOUBLE_EQ(v5.m[3], 0.0);
    ASSERT_DOUBLE_EQ(v5.m[4], 0.0);

    ASSERT_THROW(Vector<0> v, std::string);
}


TEST(Vector, CreateInitial)
{
    Vector<3> v3Initial(1.0);
    ASSERT_DOUBLE_EQ(v3Initial.m[0], 1.0);
    ASSERT_DOUBLE_EQ(v3Initial.m[1], 1.0);
    ASSERT_DOUBLE_EQ(v3Initial.m[2], 1.0);

    Vector<4> v4Initial(1.0);
    ASSERT_DOUBLE_EQ(v4Initial.m[0], 1.0);
    ASSERT_DOUBLE_EQ(v4Initial.m[1], 1.0);
    ASSERT_DOUBLE_EQ(v4Initial.m[2], 1.0);
    ASSERT_DOUBLE_EQ(v4Initial.m[3], 1.0);

    ASSERT_THROW(Vector<0> v(5.0), std::string);
}


TEST(Vector, CreateInitializerList)
{
    Vector<3> v3 {1.0, 2.0, 3.0};
    ASSERT_DOUBLE_EQ(v3.m[0], 1.0);
    ASSERT_DOUBLE_EQ(v3.m[1], 2.0);
    ASSERT_DOUBLE_EQ(v3.m[2], 3.0);

    ASSERT_THROW(Vector<3> v({1.0, 2.0}), std::string);
    ASSERT_THROW(Vector<0> v({1.0, 2.0, 3.0}), std::string);
}


TEST(Vector, Addition)
{
    Vector<3> first(1.0);
    Vector<3> second(2.0);

    Vector<3> result = first + second;
    ASSERT_DOUBLE_EQ(result.m[0], 3.0);
    ASSERT_DOUBLE_EQ(result.m[1], 3.0);
    ASSERT_DOUBLE_EQ(result.m[2], 3.0);
}


TEST(Vector, Subtraction)
{
    Vector<3> first{2.0, 4.0, 6.0};
    Vector<3> second{1.0, 6.0, 4.0};

    Vector<3> result = first - second;
    ASSERT_DOUBLE_EQ(result.m[0], 1.0);
    ASSERT_DOUBLE_EQ(result.m[1], -2.0);
    ASSERT_DOUBLE_EQ(result.m[2], 2.0);
}


TEST(Vector, Multiply)
{
    Vector<3> vec(2.0);

    Vector<3> result = vec * 4.0;
    ASSERT_DOUBLE_EQ(result.m[0], 8.0);
    ASSERT_DOUBLE_EQ(result.m[1], 8.0);
    ASSERT_DOUBLE_EQ(result.m[2], 8.0);
}


TEST(Vector, Divide)
{
    Vector<3> vec(8.0);

    Vector<3> result = vec / 4.0;
    ASSERT_DOUBLE_EQ(result.m[0], 2.0);
    ASSERT_DOUBLE_EQ(result.m[1], 2.0);
    ASSERT_DOUBLE_EQ(result.m[2], 2.0);
}


TEST(Vector, Length)
{
    Vector<3> vec;
    vec.m[0] = 2.0;
    vec.m[1] = 4.0;
    vec.m[2] = 4.0;

    ASSERT_DOUBLE_EQ(vec.length(), 6.0);
}


TEST(Vector, Normalized)
{
    Vector<3> vec;
    vec.m[0] = 2.0;
    vec.m[1] = 4.0;
    vec.m[2] = 4.0;

    Vector<3> result = vec.normalized();
    ASSERT_DOUBLE_EQ(result.length(), 1.0);
}


TEST(Vector, Dot)
{
    Vector<3> first;
    first.m[0] = 3.0;
    first.m[1] = -2.0;
    first.m[2] = 7.0;

    Vector<3> second;
    second.m[0] = 0.0;
    second.m[1] = 4.0;
    second.m[2] = -1.0;

    ASSERT_DOUBLE_EQ(first.dot(second), -15.0);
}


TEST(Vector, Cross)
{
    // Valid vector
    Vector<3> first;
    first.m[0] = 1.0;
    first.m[1] = 3.0;
    first.m[2] = -4.0;

    Vector<3> second;
    second.m[0] = 2.0;
    second.m[1] = -5.0;
    second.m[2] = 8.0;

    Vector<3> result = first.cross(second);
    ASSERT_DOUBLE_EQ(result.m[0], 4.0);
    ASSERT_DOUBLE_EQ(result.m[1], -16.0);
    ASSERT_DOUBLE_EQ(result.m[2], -11.0);

    // Invalid vector
    Vector<2> third;
    ASSERT_THROW(third.cross(second), std::string);
}
