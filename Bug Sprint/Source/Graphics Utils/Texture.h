//
//  Texture.hpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 07/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "OpenGLES.h"
#include "ShaderProgram.h"


class Texture
{
public:
    Texture();
    Texture(const std::string &fileName);
    Texture(const std::string &rightFileName, const std::string &leftFileName,
            const std::string &topFileName, const std::string &bottomFileName,
            const std::string &backFileName, const std::string frontrightFileName);
    virtual ~Texture();

    GLuint getId();
    void use(std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    GLuint textureId = 0;

    GLuint loadTextureTexture(GLint width, GLint height, GLubyte *data);
};

#endif
