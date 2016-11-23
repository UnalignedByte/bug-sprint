//
//  Texture.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 07/11/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Texture.h"

#include "Image.h"

using namespace std;


Texture::Texture()
{
}


Texture::Texture(const string &fileName)
{
    Image image(fileName);
    textureId = loadTexture(image.getWidth(), image.getHeight(), image.getData());
    type = Type2D;
    width = image.getWidth();
    height = image.getHeight();
}


Texture::Texture(const string &rightFileName, const string &leftFileName,
                 const string &topFileName, const string &bottomFileName,
                 const string &frontFileName, const string backFileName)
{
    Image rightImage(rightFileName);
    Image leftImage(leftFileName);

    Image topImage(topFileName);
    Image bottomImage(bottomFileName);

    Image frontImage(frontFileName);
    Image backImage(backFileName);

    width = rightImage.getWidth();
    height = rightImage.getHeight();

    if(leftImage.getWidth() != width || leftImage.getHeight() != height ||
       topImage.getWidth() != width || topImage.getHeight() != height ||
       bottomImage.getWidth() != width || bottomImage.getHeight() != height ||
       frontImage.getWidth() != width || frontImage.getHeight() != height ||
       backImage.getWidth() != width || backImage.getHeight() != height) {
        throw string("Cube texture image sizes are not equal");
    }

    textureId = loadCubeTexture(width, height,
                                rightImage.getData(), leftImage.getData(),
                                topImage.getData(), bottomImage.getData(),
                                frontImage.getData(), backImage.getData());
    type = TypeCube;
}


Texture::Texture(const std::string &text, const std::string &fontFileName, GLfloat fontSize, const Color &fontColor)
{
    Image image(text, fontFileName, fontSize, fontColor);
    textureId = loadTexture(image.getWidth(), image.getHeight(), image.getData());
    type = Type2D;
    width = image.getWidth();
    height = image.getHeight();
}


Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}


GLuint Texture::getId() const
{
    return textureId;
}


Texture::Type Texture::getType() const
{
    return type;
}


GLint Texture::getWidth() const
{
    return width;
}


GLint  Texture::getHeight() const
{
    return height;
}


void Texture::use(shared_ptr<ShaderProgram> shaderProgram) const
{
    if(textureId == 0)
        return;

    shaderProgram->use();

    if(type == Type2D) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        GLint diffuseSamplerId = glGetUniformLocation(shaderProgram->getId(), "diffuseSampler");
        glUniform1i(diffuseSamplerId, 0);
    } else if(type == TypeCube) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
        GLint cubeSamplerId = glGetUniformLocation(shaderProgram->getId(), "cubeSampler");
        glUniform1i(cubeSamplerId, 0);
    }
}


GLuint Texture::loadTexture(GLint width, GLint height, GLubyte *data)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    if(textureId == 0)
        throw string("Error creating texture");

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureId;
}


GLuint Texture::loadCubeTexture(GLint width, GLint height,
                                GLubyte *dataRight, GLubyte *dataLeft,
                                GLubyte *dataTop, GLubyte *dataBottom,
                                GLubyte *dataFront, GLubyte *dataBack)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    if(textureId == 0)
        throw string("Error creating texture");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    // Right
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataRight);

    // Left
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataLeft);

    // Top
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataTop);

    // Bottom
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataBottom);

    // Front
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataFront);

    // Back
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataBack);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return textureId;
}
