//
//  Instance.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 04/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Instance.h"

using namespace std;


void Instance::updateInput(const Input &input)
{
    for(shared_ptr<Instance> instance : children)
        instance->updateInput(input);
}


void Instance::update(float timeInterval)
{
    for(shared_ptr<Instance> instance : children)
        instance->update(timeInterval);
}


void Instance::addChild(std::shared_ptr<Instance> child)
{
    children.push_back(child);
    child->parent = this;
}


GLsizei Instance::getTrianglesCount() const
{
    GLsizei trianglesSum{0};
    for(shared_ptr<Instance> instance : children)
        trianglesSum += instance->getTrianglesCount();

    return trianglesSum;
}
