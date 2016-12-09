//
//  TestScene.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Scene.h"

#include "Drawable.h"


class TestScene: public Scene
{
public:
    TestScene(GLint viewWidth, GLint viewHeight);
    
    void loadScene() override;
    void update(float timeInterval) override;

protected:
    std::shared_ptr<Drawable> monkey;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Light> light;
};

#endif
