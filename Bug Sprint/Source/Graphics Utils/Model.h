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
#include "OpenGLES.h"

#include "ShaderProgram.h"
#include "Matrix.h"
#include "Color.h"


class Model
{
public:
    Model(const std::string &fileName);
    ~Model();

    GLsizei getTrianglesCount() const;
    bool getHasTexCoords() const;

    Color getColor() const;
    void setColor(const Color &color);
    GLfloat getAmbientIntensity() const;
    void setAmbientIntensity(GLfloat intensity);
    GLfloat getDiffuseIntensity() const;
    void setDiffuseIntensity(GLfloat intensity);
    GLfloat getSpecularIntensity() const;
    void setSpecularIntensity(GLfloat intensity);

    void draw(std::shared_ptr<ShaderProgram> shaderProgram, Matrix4 &modelMatrix);

protected:
    GLuint vertexArrayId;

    GLsizei trianglesCount;
    bool hasTexCoords;

    Color color = {0.5, 0.5, 0.5, 1.0};
    GLfloat ambientIntensity = 0.2;
    GLfloat diffuseIntensity = 0.8;
    GLfloat specularIntensity = 10.0;

protected:
    void loadObj(const std::string &fileString);
};

#endif
