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

#include "ShaderProgram.h"
#include "Matrix.h"


class Model
{
public:
    Model(const std::string &fileName);
    ~Model();

    GLsizei getTrianglesCount() const;

    void draw(std::shared_ptr<ShaderProgram> shaderProgram, Matrix4 &modelMatrix);

protected:
    GLuint vertexArrayId;
    GLsizei trianglesCount;

protected:
    void loadObj(const std::string &fileString);
};

#endif
