//
//  ShaderProgram.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <OpenGLES/ES3/gl.h>


class ShaderProgram
{
public:
    ShaderProgram(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);
    ~ShaderProgram();
    GLuint getId();
    void use();

private:
    GLuint programId;

    GLuint loadShader(GLuint type, const std::string &sourceString);
    GLuint loadProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
};

#endif
