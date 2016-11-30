//
//  VectorTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 13/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "Vector.h"

using namespace std;


TEST(Vector, CreateDefault)
{
    Vector<3> v3;
    ASSERT_DOUBLE_EQ(v3[0], 0.0);
    ASSERT_DOUBLE_EQ(v3[1], 0.0);
    ASSERT_DOUBLE_EQ(v3[2], 0.0);

    Vector<5> v5;
    ASSERT_DOUBLE_EQ(v5[0], 0.0);
    ASSERT_DOUBLE_EQ(v5[1], 0.0);
    ASSERT_DOUBLE_EQ(v5[2], 0.0);
    ASSERT_DOUBLE_EQ(v5[3], 0.0);
    ASSERT_DOUBLE_EQ(v5[4], 0.0);

    ASSERT_THROW(Vector<0> v, string);
}


TEST(Vector, CreateInitial)
{
    Vector<3> v3Initial(1.0);
    ASSERT_DOUBLE_EQ(v3Initial[0], 1.0);
    ASSERT_DOUBLE_EQ(v3Initial[1], 1.0);
    ASSERT_DOUBLE_EQ(v3Initial[2], 1.0);

    Vector<4> v4Initial(1.0);
    ASSERT_DOUBLE_EQ(v4Initial[0], 1.0);
    ASSERT_DOUBLE_EQ(v4Initial[1], 1.0);
    ASSERT_DOUBLE_EQ(v4Initial[2], 1.0);
    ASSERT_DOUBLE_EQ(v4Initial[3], 1.0);

    ASSERT_THROW(Vector<0> v(5.0), string);
}


TEST(Vector, CreateInitializerList)
{
    Vector<3> v3{1.0, 2.0, 3.0};
    ASSERT_DOUBLE_EQ(v3[0], 1.0);
    ASSERT_DOUBLE_EQ(v3[1], 2.0);
    ASSERT_DOUBLE_EQ(v3[2], 3.0);

    ASSERT_THROW(Vector<3> v({1.0}), string);
    ASSERT_THROW(Vector<3> v({1.0, 2.0}), string);
    ASSERT_THROW(Vector<0> v({1.0, 2.0, 3.0}), string);
}


TEST(Vector, RuleOfFive)
{
    Vector3 v3{1.0, 2.0, 3.0};

    // Copy constructor
    Vector3 copy0(v3);
    ASSERT_EQ(copy0[0], 1.0);
    ASSERT_EQ(copy0[1], 2.0);
    ASSERT_EQ(copy0[2], 3.0);

    // Copy assignment
    Vector3 copy1 = v3;
    ASSERT_EQ(copy1[0], 1.0);
    ASSERT_EQ(copy1[1], 2.0);
    ASSERT_EQ(copy1[2], 3.0);

    // Move constructor
    Vector3 move0(std::move(v3));
    ASSERT_EQ(move0[0], 1.0);
    ASSERT_EQ(move0[1], 2.0);
    ASSERT_EQ(move0[2], 3.0);

    // Move assignment
    Vector3 move1 = std::move(v3);
    ASSERT_EQ(move1[0], 1.0);
    ASSERT_EQ(move1[1], 2.0);
    ASSERT_EQ(move1[2], 3.0);
}


TEST(Vector, Addition)
{
    Vector<3> first(1.0);
    Vector<3> second(2.0);

    Vector<3> result = first + second;
    ASSERT_DOUBLE_EQ(result[0], 3.0);
    ASSERT_DOUBLE_EQ(result[1], 3.0);
    ASSERT_DOUBLE_EQ(result[2], 3.0);
}


TEST(Vector, Subtraction)
{
    Vector<3> first{2.0, 4.0, 6.0};
    Vector<3> second{1.0, 6.0, 4.0};

    Vector<3> result = first - second;
    ASSERT_DOUBLE_EQ(result[0], 1.0);
    ASSERT_DOUBLE_EQ(result[1], -2.0);
    ASSERT_DOUBLE_EQ(result[2], 2.0);
}


TEST(Vector, Multiply)
{
    Vector<3> vec(2.0);

    Vector<3> result = vec * 4.0;
    ASSERT_DOUBLE_EQ(result[0], 8.0);
    ASSERT_DOUBLE_EQ(result[1], 8.0);
    ASSERT_DOUBLE_EQ(result[2], 8.0);
}


TEST(Vector, Divide)
{
    Vector<3> vec(8.0);

    Vector<3> result = vec / 4.0;
    ASSERT_DOUBLE_EQ(result[0], 2.0);
    ASSERT_DOUBLE_EQ(result[1], 2.0);
    ASSERT_DOUBLE_EQ(result[2], 2.0);
}


TEST(Vector, Length)
{
    Vector<3> vec;
    vec[0] = 2.0;
    vec[1] = 4.0;
    vec[2] = 4.0;

    ASSERT_DOUBLE_EQ(vec.length(), 6.0);
}


TEST(Vector, Normalized)
{
    Vector<3> vec;
    vec[0] = 2.0;
    vec[1] = 4.0;
    vec[2] = 4.0;

    Vector<3> result = vec.normalized();
    ASSERT_DOUBLE_EQ(result.length(), 1.0);
}


TEST(Vector, Dot)
{
    Vector<3> first;
    first[0] = 3.0;
    first[1] = -2.0;
    first[2] = 7.0;

    Vector<3> second;
    second[0] = 0.0;
    second[1] = 4.0;
    second[2] = -1.0;

    ASSERT_DOUBLE_EQ(first.dot(second), -15.0);
}


TEST(Vector, Cross)
{
    // Valid vector
    Vector<3> first;
    first[0] = 1.0;
    first[1] = 3.0;
    first[2] = -4.0;

    Vector<3> second;
    second[0] = 2.0;
    second[1] = -5.0;
    second[2] = 8.0;

    Vector<3> result = first.cross(second);
    ASSERT_DOUBLE_EQ(result[0], 4.0);
    ASSERT_DOUBLE_EQ(result[1], -16.0);
    ASSERT_DOUBLE_EQ(result[2], -11.0);

    // Invalid vector
    Vector<2> third;
    ASSERT_THROW(third.cross(second), string);
}
