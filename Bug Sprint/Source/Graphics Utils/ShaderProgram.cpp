//
//  ShaderProgram.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "ShaderProgram.h"

#include "File.h"

using namespace std;


ShaderProgram::ShaderProgram(const string &vertexShaderFileName, const string &fragmentShaderFileName)
{
    // Vertex shader
    File vertexFile(vertexShaderFileName);
    GLuint vertexShaderId = loadShader(GL_VERTEX_SHADER, vertexFile.getString());

    // Fragment shader
    File fragmentFile(fragmentShaderFileName);
    GLuint fragmentShaderId = loadShader(GL_FRAGMENT_SHADER, fragmentFile.getString());

    programId = loadProgram(vertexShaderId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}


ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programId);
}


GLuint ShaderProgram::getId()
{
    return programId;
}


void ShaderProgram::use()
{
    glUseProgram(programId);
}


GLuint ShaderProgram::loadShader(GLuint type, const std::string &sourceString)
{
    const GLchar *source = (const GLchar *)sourceString.c_str();
    GLuint shaderId = glCreateShader(type);
    if(shaderId == 0)
        throw string("Error creating shader");

    glShaderSource(shaderId, 1, &source, NULL);
    glCompileShader(shaderId);

    GLint isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled) {
        GLint infoLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLength);

        if(infoLength > 0) {
            GLchar *infoBuffer = new GLchar[infoLength];
            glGetShaderInfoLog(shaderId, infoLength, NULL, infoBuffer);
            string infoString = string(infoBuffer);
            delete[] infoBuffer;

            throw new string("Error compiling shader:\n" + infoString);
        }
    }

    return shaderId;
}


GLuint ShaderProgram::loadProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
    GLuint programId = glCreateProgram();
    if(programId == 0)
        throw string("Error creating program");

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    GLint isLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if(!isLinked) {
        GLint infoLength;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLength);

        if(infoLength > 0) {
            GLchar *infoBuffer = new GLchar[infoLength];
            glGetProgramInfoLog(programId, infoLength, NULL, infoBuffer);
            string infoString = string(infoBuffer);
            delete[] infoBuffer;

            throw new string("Error linking program:\n" + infoString);
        }
    }

    return programId;
}
