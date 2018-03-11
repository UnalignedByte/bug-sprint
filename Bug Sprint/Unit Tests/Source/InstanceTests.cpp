//
//  LightTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include <memory>

#include "ShaderProgram.h"
#include "Instance.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"

using namespace std;


TEST(Instance, Create)
{
    shared_ptr<ShaderProgram> shaderProgram;

    ASSERT_NO_THROW(shaderProgram = make_shared<ShaderProgram>("vertex.vsh", "fragment.fsh"));

    ASSERT_NO_THROW(Instance instance);
    //ASSERT_NO_THROW(Drawable drawable("box.obj", shaderProgram));
    ASSERT_NO_THROW(Camera camera(200.0, 100.0, 10.0));
    ASSERT_NO_THROW(Camera camera(200.0, 100.0, 10.0, 60.0));
    ASSERT_NO_THROW(Light light(200.0, 100.0));
}
