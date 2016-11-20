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
#include <memory>
#include "OpenGLES.h"
#include "ShaderProgram.h"


class Texture
{
public:
    enum Type {
        Type2D,
        TypeCube
    };

public:
    Texture();
    Texture(const std::string &fileName);
    Texture(const std::string &rightFileName, const std::string &leftFileName,
            const std::string &topFileName, const std::string &bottomFileName,
            const std::string &frontFileName, const std::string backFileName);
    virtual ~Texture();

    GLuint getId() const;
    Type getType() const;
    GLint getWidth() const;
    GLint getHeight() const;
    
    void use(std::shared_ptr<ShaderProgram> shaderProgram) const;

protected:
    GLuint textureId = 0;
    Type type;
    GLint width;
    GLint height;

    GLuint loadTexture(GLint width, GLint height, GLubyte *data);
    GLuint loadCubeTexture(GLint width, GLint height,
                           GLubyte *dataRight, GLubyte *dataLeft,
                           GLubyte *dataTop, GLubyte *dataBottom,
                           GLubyte *dataFront, GLubyte *dataBack);
};

#endif
