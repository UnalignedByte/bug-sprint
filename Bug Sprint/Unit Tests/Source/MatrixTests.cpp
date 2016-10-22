//
//  MatrixTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 15/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "Matrix.h"

using namespace std;


TEST(Matrix, CreateDefault)
{
    Matrix<2> m;
    ASSERT_DOUBLE_EQ(m[0][0], 1.0);
    ASSERT_DOUBLE_EQ(m[0][1], 0.0);
    ASSERT_DOUBLE_EQ(m[1][0], 0.0);
    ASSERT_DOUBLE_EQ(m[1][1], 1.0);

    ASSERT_THROW(Matrix<0> m, string);
}


TEST(Matrix, CreateInitial)
{
    Matrix<2> m2(1.0);
    ASSERT_DOUBLE_EQ(m2[0][0], 1.0);
    ASSERT_DOUBLE_EQ(m2[0][1], 1.0);
    ASSERT_DOUBLE_EQ(m2[1][0], 1.0);
    ASSERT_DOUBLE_EQ(m2[1][1], 1.0);

    Matrix<3> m3(2.0);
    ASSERT_DOUBLE_EQ(m3[0][0], 2.0);
    ASSERT_DOUBLE_EQ(m3[0][1], 2.0);
    ASSERT_DOUBLE_EQ(m3[0][2], 2.0);

    ASSERT_DOUBLE_EQ(m3[1][0], 2.0);
    ASSERT_DOUBLE_EQ(m3[1][1], 2.0);
    ASSERT_DOUBLE_EQ(m3[1][2], 2.0);

    ASSERT_DOUBLE_EQ(m3[2][0], 2.0);
    ASSERT_DOUBLE_EQ(m3[2][1], 2.0);
    ASSERT_DOUBLE_EQ(m3[2][2], 2.0);

    ASSERT_THROW(Matrix<0> m(6.0), string);
}


TEST(Matrix, CreateInitializerList)
{
    Matrix<2> m{{1.0, 2.0}, {3.0, 4.0}};
    ASSERT_DOUBLE_EQ(m[0][0], 1.0);
    ASSERT_DOUBLE_EQ(m[0][1], 2.0);
    ASSERT_DOUBLE_EQ(m[1][0], 3.0);
    ASSERT_DOUBLE_EQ(m[1][1], 4.0);

    ASSERT_THROW(Matrix<0> m, string);
    ASSERT_THROW(Matrix<2> m({1.0, 2.0, 3.0}), string);
    ASSERT_THROW(Matrix<2> m({{1.0, 2.0}, 3.0, 2.0}), string);
}


TEST(Matrix, MultiplyByScalar)
{
    Matrix<2> m{{1.0, 2.0}, {3.0, 4.0}};
    Matrix<2> result = m * 3.0;

    ASSERT_DOUBLE_EQ(result[0][0], 3.0);
    ASSERT_DOUBLE_EQ(result[0][1], 6.0);
    ASSERT_DOUBLE_EQ(result[1][0], 9.0);
    ASSERT_DOUBLE_EQ(result[1][1], 12.0);
}


TEST(Matrix, MultiplyByMatrix)
{
    Matrix<3> first{{1.0, -5.0,  3.0},
                    {0.0, -2.0,  6.0},
                    {7.0,  2.0, -4.0}};
    Matrix<3> second{{-8.0, 6.0,  1.0},
                     { 7.0, 0.0, -3.0},
                     { 2.0, 4.0,  5.0}};

    Matrix<3> result = first * second;

    ASSERT_DOUBLE_EQ(result[0][0], -37.0);
    ASSERT_DOUBLE_EQ(result[0][1], 18.0);
    ASSERT_DOUBLE_EQ(result[0][2], 31.0);

    ASSERT_DOUBLE_EQ(result[1][0], -2.0);
    ASSERT_DOUBLE_EQ(result[1][1], 24.0);
    ASSERT_DOUBLE_EQ(result[1][2], 36.0);

    ASSERT_DOUBLE_EQ(result[2][0], -50.0);
    ASSERT_DOUBLE_EQ(result[2][1], 26.0);
    ASSERT_DOUBLE_EQ(result[2][2], -19.0);
}


TEST(Matrix, Translation)
{
    Matrix4 t = Matrix4::translation(3.0, 4.0, 1.5);
    ASSERT_FLOAT_EQ(t[0][0], 1.0);
    ASSERT_FLOAT_EQ(t[0][1], 0.0);
    ASSERT_FLOAT_EQ(t[0][2], 0.0);
    ASSERT_FLOAT_EQ(t[0][3], 0.0);

    ASSERT_FLOAT_EQ(t[1][0], 0.0);
    ASSERT_FLOAT_EQ(t[1][1], 1.0);
    ASSERT_FLOAT_EQ(t[1][2], 0.0);
    ASSERT_FLOAT_EQ(t[1][3], 0.0);

    ASSERT_FLOAT_EQ(t[2][0], 0.0);
    ASSERT_FLOAT_EQ(t[2][1], 0.0);
    ASSERT_FLOAT_EQ(t[2][2], 1.0);
    ASSERT_FLOAT_EQ(t[2][3], 0.0);

    ASSERT_FLOAT_EQ(t[3][0], 3.0);
    ASSERT_FLOAT_EQ(t[3][1], 4.0);
    ASSERT_FLOAT_EQ(t[3][2], 1.5);
    ASSERT_FLOAT_EQ(t[3][3], 1.0);
}


TEST(Matrix, Scale)
{
    Matrix4 t = Matrix4::scale(2.0, 3.0, 4.0);
    ASSERT_FLOAT_EQ(t[0][0], 2.0);
    ASSERT_FLOAT_EQ(t[0][1], 0.0);
    ASSERT_FLOAT_EQ(t[0][2], 0.0);
    ASSERT_FLOAT_EQ(t[0][3], 0.0);

    ASSERT_FLOAT_EQ(t[1][0], 0.0);
    ASSERT_FLOAT_EQ(t[1][1], 3.0);
    ASSERT_FLOAT_EQ(t[1][2], 0.0);
    ASSERT_FLOAT_EQ(t[1][3], 0.0);

    ASSERT_FLOAT_EQ(t[2][0], 0.0);
    ASSERT_FLOAT_EQ(t[2][1], 0.0);
    ASSERT_FLOAT_EQ(t[2][2], 4.0);
    ASSERT_FLOAT_EQ(t[2][3], 0.0);

    ASSERT_FLOAT_EQ(t[3][0], 0.0);
    ASSERT_FLOAT_EQ(t[3][1], 0.0);
    ASSERT_FLOAT_EQ(t[3][2], 0.0);
    ASSERT_FLOAT_EQ(t[3][3], 1.0);
}
