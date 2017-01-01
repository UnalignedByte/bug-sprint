//
//  Drawable2D.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 01/01/2017.
//  Copyright © 2017 UnalignedByte. All rights reserved.
//

#include "Drawable2D.h"

using namespace std;


void Drawable2D::draw(std::shared_ptr<ShaderProgram> shaderProgram)
{
    for(shared_ptr<Instance> child : children) {
        if(shared_ptr<Drawable2D> drawable = dynamic_pointer_cast<Drawable2D>(child))
            drawable->draw(shaderProgram);
    }
}
