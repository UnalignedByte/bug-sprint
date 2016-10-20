//
//  ShaderProgramTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include "ShaderProgram.h"


TEST(ShaderProgram, LoadInvalid)
{
    ASSERT_THROW(ShaderProgram sp("wrong_file", "wrong_file"), std::string);
    ASSERT_THROW(ShaderProgram sp("broken_vertex.vsh", "broken_fragment.fsh"), std::string);
}


TEST(ShaderProgram, LoadValid)
{
    ASSERT_NO_THROW(ShaderProgram sp("vertex.vsh", "fragment.fsh"));
}
