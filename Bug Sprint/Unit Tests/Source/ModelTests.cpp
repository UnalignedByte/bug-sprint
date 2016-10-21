//
//  ModelTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include <memory>
#include "Model.h"
#include "ShaderProgram.h"


TEST(Model, Load)
{
    ASSERT_NO_THROW(Model m("box.obj"));
}
