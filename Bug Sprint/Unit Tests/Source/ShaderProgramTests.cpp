//
//  ShaderProgramTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "ShaderProgram.h"

using namespace std;


TEST(ShaderProgram, LoadInvalid)
{
    ASSERT_THROW(ShaderProgram sp("wrong_file", "wrong_file"), string);
    ASSERT_THROW(ShaderProgram sp("broken_vertex.vsh", "broken_fragment.fsh"), string);
}


TEST(ShaderProgram, LoadValid)
{
    //ASSERT_NO_THROW(ShaderProgram sp("vertex.vsh", "fragment.fsh"));
}
