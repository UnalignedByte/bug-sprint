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

using namespace std;


TEST(Model, Load)
{
    std::shared_ptr<Model> m;
    ASSERT_NO_THROW(m = make_shared<Model>("box.obj"));
    ASSERT_EQ(m->getTrianglesCount(), 12);
}
