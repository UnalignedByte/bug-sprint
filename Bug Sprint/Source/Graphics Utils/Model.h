//
//  Model.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <string>
#include <vector>
#include <OpenGLES/ES3/gl.h>
#include "File.h"
#include "ShaderProgram.h"
#include "Matrix.h"


class Model
{
public:
    Model(const std::string &fileName, std::shared_ptr<ShaderProgram> shaderProgram);
    ~Model();

    void draw(Matrix4 &model, Matrix4 &view, Matrix4 &projection);

private:
    GLuint vertexArrayId;

    std::shared_ptr<ShaderProgram> shaderProgram;
    std::vector<GLushort> indices;
    void loadObj(const std::string &fileString);

public:
    typedef struct {
        GLfloat position[3];
        GLfloat color[4];
    } Vertex;
};

#endif
