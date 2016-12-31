//
//  DebugSprite.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 29/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef DEBUG_SPRITE_H
#define DEBUG_SPRITE_H

#include "Instance2D.h"

struct Vertex {
    GLfloat position[2];
    GLfloat texCoords[2];
};

class DebugSprite: public Instance2D
{
public:
    DebugSprite(GLint textureId, GLfloat width, GLfloat height);
    void draw(std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    GLint textureId;
    //Vertex vertices[6];
    GLfloat vertices[12];
    GLfloat texCoords[12];
};

#endif
