//
//  Shader.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 16/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Shader.h"

#include <fstream>

using namespace std;


Shader::Shader(const string &vertexShaderFilePath, const string &fragmentShaderFilePath)
{
    // Vertex shader
    //string vertexShaderSource = readFile(vertexShaderFilePath);
    //GLuint vertexShaderId = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
}


GLuint Shader::loadShader(GLuint type, const std::string &source)
{
    GLuint shaderId = glCreateShader(type);

    return shaderId;
}
