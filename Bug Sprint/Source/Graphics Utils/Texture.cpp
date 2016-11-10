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
    textureId = loadTextureTexture(image.getWidth(), image.getHeight(), image.getData());
}


Texture::Texture(const string &rightFileName, const string &leftFileName,
                 const string &topFileName, const string &bottomFileName,
                 const string &backFileName, const string frontrightFileName)
{
}


Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}


GLuint Texture::getId()
{
    return textureId;
}


void Texture::use(shared_ptr<ShaderProgram> shaderProgram)
{
    if(textureId == 0)
        return;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    GLint diffuseSamplerId = glGetUniformLocation(shaderProgram->getId(), "diffuseSampler");
    glUniform1i(diffuseSamplerId, 0);
}


GLuint Texture::loadTextureTexture(GLint width, GLint height, GLubyte *data)
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
