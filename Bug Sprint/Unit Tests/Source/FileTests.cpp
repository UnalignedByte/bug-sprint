//
//  FileTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "File.h"

using namespace std;


TEST(File, Open)
{
    File file("test.txt");
    ASSERT_NE(file.getFilePath(), "");

    ASSERT_THROW(File file("wrong.txt"), string);
}


TEST(File, ReadString)
{
    File file("test.txt");
    ASSERT_NE(file.getString(), "");
}
