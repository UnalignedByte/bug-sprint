//
//  Instance3DTests.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 18/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include <gtest/gtest.h>

#include <memory>
#include "Instance3D.h"

using namespace std;


TEST(Instance3D, CreateDefatult)
{
    Instance3D instance;

    ASSERT_FLOAT_EQ(instance.position[0], 0.0);
    ASSERT_FLOAT_EQ(instance.position[1], 0.0);
    ASSERT_FLOAT_EQ(instance.position[2], 0.0);

    ASSERT_FLOAT_EQ(instance.scale[0], 1.0);
    ASSERT_FLOAT_EQ(instance.scale[1], 1.0);
    ASSERT_FLOAT_EQ(instance.scale[2], 1.0);

    ASSERT_FLOAT_EQ(instance.rotation[0], 0.0);
    ASSERT_FLOAT_EQ(instance.rotation[1], 0.0);
    ASSERT_FLOAT_EQ(instance.rotation[2], 0.0);

    ASSERT_EQ(instance.getTrianglesCount(), 0);
}


TEST(Instance3D, LocalCoordinateSystem)
{
    Instance3D instance;

    instance.position = {1.0, 2.0, 3.0};
    instance.rotation = {20.0, 30.0, 90.0};

    ASSERT_FLOAT_EQ(instance.position[0], 1.0);
    ASSERT_FLOAT_EQ(instance.position[1], 2.0);
    ASSERT_FLOAT_EQ(instance.position[2], 3.0);

    ASSERT_FLOAT_EQ(instance.rotation[0], 20.0);
    ASSERT_FLOAT_EQ(instance.rotation[1], 30.0);
    ASSERT_FLOAT_EQ(instance.rotation[2], 90.0);

    Vector3 worldPosition = instance.getWorldPosition();
    ASSERT_FLOAT_EQ(worldPosition[0], 1.0);
    ASSERT_FLOAT_EQ(worldPosition[1], 2.0);
    ASSERT_FLOAT_EQ(worldPosition[2], 3.0);

    Vector3 worldScale = instance.getWorldScale();
    ASSERT_FLOAT_EQ(worldScale[0], 1.0);
    ASSERT_FLOAT_EQ(worldScale[1], 1.0);
    ASSERT_FLOAT_EQ(worldScale[2], 1.0);

    Vector3 worldRotation = instance.getWorldRotation();
    ASSERT_FLOAT_EQ(worldRotation[0], 20.0);
    ASSERT_FLOAT_EQ(worldRotation[1], 30.0);
    ASSERT_FLOAT_EQ(worldRotation[2], 90.0);
}


TEST(Instance3D, WorldCoordinateSystem)
{
    Instance3D parent;
    parent.position = {5.0, 3.0, 2.0};

    // Translation only
    shared_ptr<Instance3D> child = make_shared<Instance3D>();
    parent.addChild(child);

    child->position = {-8.0, 9.0, 13.0};
    child->rotation = {90.0, 0.0, 20.0};

    parent.update(0);

    {
        Vector3 worldPosition = child->getWorldPosition();
        ASSERT_FLOAT_EQ(worldPosition[0], -3.0);
        ASSERT_FLOAT_EQ(worldPosition[1], 12.0);
        ASSERT_FLOAT_EQ(worldPosition[2], 15.0);

        Vector3 worldRotation = child->getWorldRotation();
        ASSERT_FLOAT_EQ(worldRotation[0], 90.0);
        ASSERT_FLOAT_EQ(worldRotation[1], 0.0);
        ASSERT_FLOAT_EQ(worldRotation[2], 20.0);
    }

    // Rotation only
    parent.position = {0.0, 0.0, 0.0};
    parent.rotation = {0.0, 45.0, 0.0};

    child->position = {0.0, 0.0, 1.0};

    parent.update(0);

    {
        Vector3 worldPosition = child->getWorldPosition();
        ASSERT_FLOAT_EQ(worldPosition[0], sin(45.0 * M_PI / 180.0));
        ASSERT_FLOAT_EQ(worldPosition[1], 0.0);
        ASSERT_FLOAT_EQ(worldPosition[2], cos(45.0 * M_PI / 180.0));

        Vector3 worldRotation = child->getWorldRotation();
        ASSERT_FLOAT_EQ(worldRotation[0], 90.0);
        ASSERT_FLOAT_EQ(worldRotation[1], 45.0);
        ASSERT_FLOAT_EQ(worldRotation[2], 20.0);
    }
}
