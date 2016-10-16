//
//  MatrixTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 15/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "Matrix.h"


TEST(Matrix, CreateDefault)
{
    Matrix<2> m;
    ASSERT_DOUBLE_EQ(m[0][0], 0.0);
    ASSERT_DOUBLE_EQ(m[0][1], 0.0);
    ASSERT_DOUBLE_EQ(m[1][0], 0.0);
    ASSERT_DOUBLE_EQ(m[1][1], 0.0);

    ASSERT_THROW(Matrix<0> m, std::string);
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

    ASSERT_THROW(Matrix<0> m(6.0), std::string);
}


TEST(Matrix, CreateInitializerList)
{
    Matrix<2> m{{1.0, 2.0}, {3.0, 4.0}};
    ASSERT_DOUBLE_EQ(m[0][0], 1.0);
    ASSERT_DOUBLE_EQ(m[0][1], 2.0);
    ASSERT_DOUBLE_EQ(m[1][0], 3.0);
    ASSERT_DOUBLE_EQ(m[1][1], 4.0);

    ASSERT_THROW(Matrix<0> m, std::string);
    ASSERT_THROW(Matrix<2> m({1.0, 2.0, 3.0}), std::string);
    ASSERT_THROW(Matrix<2> m({{1.0, 2.0}, 3.0, 2.0}), std::string);
}
