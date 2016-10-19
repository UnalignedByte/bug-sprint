//
//  Model.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "Model.h"

#include <sstream>
#include <vector>

#include "Matrix.h"

using namespace std;


Model::Model(const string &fileName, shared_ptr<ShaderProgram> shaderProgram) : shaderProgram(shaderProgram)
{
    File modelFile(fileName);
    loadObj(modelFile.getString());
}


Model::~Model()
{
    glDeleteVertexArrays(1, &vertexArrayId);
}


void Model::loadObj(const std::string &fileString)
{
    stringstream stream(fileString);

    vector<Vertex> vertices;

    string lineBuffer;
    while(getline(stream, lineBuffer)) {
        string type;
        string first;
        string second;
        string third;
        string fourth;

        istringstream inStream(lineBuffer);
        inStream >> type >> first >> second >> third >> fourth;

        if(type == "v") {
            GLfloat x = atof(first.c_str());
            GLfloat y = atof(second.c_str());
            GLfloat z = atof(third.c_str());

            Vertex vertex{{x, y, z},
                          {x, y, z, 1.0}};
            vertices.push_back(vertex);
        } else if(type == "f") {
            GLushort v1 = GLushort(stoi(first)-1);
            GLushort v2 = GLushort(stoi(second)-1);
            GLushort v3 = GLushort(stoi(third)-1);
            indices.push_back(v1);
            indices.push_back(v2);
            indices.push_back(v3);
        }
    }

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}


void Model::update()
{
    GLfloat ratio = 568.0/320.0;
    GLint projectionMatrixId = glGetUniformLocation(shaderProgram->getId(), "projectionMatrix");
    Matrix4 projectionMatrix = Matrix4::perspectiveProjection(60.0, ratio, 0.1, 100.0);
    glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, projectionMatrix.getData());

    GLint modelMatrixId = glGetUniformLocation(shaderProgram->getId(), "modelMatrix");
    static GLfloat angle = 0.0;
    Matrix4 modelMatrix = Matrix4::yRotation(angle);
    angle += 2.0;
    modelMatrix = modelMatrix * Matrix4::translation(0.0, 0.0, -2.0);
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, modelMatrix.getData());
}


void Model::draw()
{
    shaderProgram->use();

    glBindVertexArray(vertexArrayId);
    glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_SHORT, &indices[0]);
}
