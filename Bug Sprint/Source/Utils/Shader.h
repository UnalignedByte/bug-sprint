//
//  Shader.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <OpenGLES/ES3/gl.h>


class Shader
{
public:
    Shader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

private:
    GLuint loadShader(GLuint type, const std::string &source);
};

#endif
