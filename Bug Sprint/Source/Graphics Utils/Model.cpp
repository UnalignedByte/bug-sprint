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
#include <cstdio>

#include "File.h"
#include "ShaderProgram.h"


using namespace std;


struct Vertex {
    GLfloat position[3];
    GLfloat normal[3];
    GLfloat texCoord[2];
};


struct MaterialUniform {
    GLfloat color[3];
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
    GLfloat specularIntensity;
};


Model::Model(const string &fileName)
{
    File modelFile(fileName);
    loadObj(modelFile.getString());
}


Model::~Model()
{
    glDeleteVertexArrays(1, &vertexArrayId);
}


GLsizei Model::getTrianglesCount() const
{
    return trianglesCount;
}


bool Model::getHasTexCoords() const
{
    return hasTexCoords;
}


Color Model::getColor() const
{
    return color;
}


void Model::setColor(const Color &color)
{
    this->color = color;
}


GLfloat Model::getAmbientIntensity() const
{
    return ambientIntensity;
}


void Model::setAmbientIntensity(GLfloat intensity)
{
    ambientIntensity = intensity;
}


GLfloat Model::getDiffuseIntensity() const
{
    return diffuseIntensity;
}


void Model::setDiffuseIntensity(GLfloat intensity)
{
    diffuseIntensity = intensity;
}


GLfloat Model::getSpecularIntensity() const
{
    return specularIntensity;
}


void Model::setSpecularIntensity(GLfloat intensity)
{
    specularIntensity = intensity;
}


void Model::draw(shared_ptr<ShaderProgram> shaderProgram, Matrix4 &modelMatrix)
{
    shaderProgram->use();

    GLint modelMatrixId = glGetUniformLocation(shaderProgram->getId(), "modelMatrix");
    Matrix4 modelMatrixCopy = modelMatrix;
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, modelMatrixCopy.getData());

    GLint materialColorId = glGetUniformLocation(shaderProgram->getId(), "material.color");
    glUniform3f(materialColorId, color[0], color[1], color[2]);

    GLint ambientIntensityId = glGetUniformLocation(shaderProgram->getId(), "material.ambientIntensity");
    glUniform1f(ambientIntensityId, ambientIntensity);

    GLint diffuseIntensityId = glGetUniformLocation(shaderProgram->getId(), "material.diffuseIntensity");
    glUniform1f(diffuseIntensityId, diffuseIntensity);

    GLint specularIntensityId = glGetUniformLocation(shaderProgram->getId(), "material.specularIntensity");
    glUniform1f(specularIntensityId, specularIntensity);

    glBindVertexArray(vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, trianglesCount * 3);
}


void Model::loadObj(const std::string &fileString)
{
    stringstream stream(fileString);

    vector<Vertex> modelData;

    vector<Vector3> vertices;
    vector<Vector3> normals;
    vector<Vector2> texCoords;

    trianglesCount = 0;

    string lineBuffer;
    while(getline(stream, lineBuffer)) {
        string type;

        istringstream inStream(lineBuffer);
        inStream >> type;

        if(type == "v") {
            GLfloat x;
            GLfloat y;
            GLfloat z;

            inStream >> x >> y >> z;

            vertices.push_back(Vector3({x, y, z}));
        } else if(type == "vn") {
            GLfloat x;
            GLfloat y;
            GLfloat z;

            inStream >> x >> y >> z;

            normals.push_back(Vector3({x, y, z}));
        } else if(type == "vt") {
            GLfloat u;
            GLfloat v;

            inStream >> u >> v;

            texCoords.push_back(Vector2({u, v}));
        } else if(type == "f") {
            hasTexCoords = texCoords.size() > 0;

            int vIndex0;
            int vtIndex0;
            int nIndex0;

            int vIndex1;
            int vtIndex1;
            int nIndex1;

            int vIndex2;
            int vtIndex2;
            int nIndex2;

            if(hasTexCoords) {
                sscanf(lineBuffer.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &vIndex0, &vtIndex0, &nIndex0,
                       &vIndex1, &vtIndex1, &nIndex1,
                       &vIndex2, &vtIndex2, &nIndex2);
            } else {
                sscanf(lineBuffer.c_str(), "f %d//%d %d//%d %d//%d", &vIndex0, &nIndex0,
                       &vIndex1, &nIndex1,
                       &vIndex2, &nIndex2);
            }

            // Indexing in obj file starts at 1
            vIndex0--;
            vtIndex0--;
            nIndex0--;

            vIndex1--;
            vtIndex1--;
            nIndex1--;

            vIndex2--;
            vtIndex2--;
            nIndex2--;

            // Vertex 0
            if(vIndex0 < 0 || vIndex0 >= vertices.size())
                throw string("Index out of bounds");
            if(hasTexCoords && (vtIndex0 < 0 || vtIndex0 >= texCoords.size()))
                throw string("Index out of bounds");
            if(nIndex0 < 0 || nIndex0 >= normals.size())
                throw string("Index out of bounds");

            Vector3 &vertex0 = vertices[vIndex0];
            Vector3 &normal0 = normals[nIndex0];
            GLfloat u0 = hasTexCoords ? texCoords[vtIndex0][0] : 0.0;
            GLfloat v0 = hasTexCoords ? texCoords[vtIndex0][1] : 0.0;

            Vertex modelVertex0{
                {vertex0[0], vertex0[1], vertex0[2]},
                {normal0[0], normal0[1], normal0[2]},
                {u0, v0}};
            modelData.push_back(modelVertex0);

            // Vertex 1
            if(vIndex1 < 0 || vIndex1 >= vertices.size())
                throw string("Index out of bounds");
            if(hasTexCoords && (vtIndex1 < 0 || vtIndex1 >= texCoords.size()))
                throw string("Index out of bounds");
            if(nIndex1 < 0 || nIndex1 >= normals.size())
                throw string("Index out of bounds");

            Vector3 &vertex1 = vertices[vIndex1];
            Vector3 &normal1 = normals[nIndex1];
            GLfloat u1 = hasTexCoords ? texCoords[vtIndex1][0] : 0.0;
            GLfloat v1 = hasTexCoords ? texCoords[vtIndex1][1] : 0.0;

            Vertex modelVertex1{
                {vertex1[0], vertex1[1], vertex1[2]},
                {normal1[0], normal1[1], normal1[2]},
                {u1, v1}};
            modelData.push_back(modelVertex1);

            // Vertex 2
            if(vIndex2 < 0 || vIndex2 >= vertices.size())
                throw string("Index out of bounds");
            if(hasTexCoords && (vtIndex2 < 0 || vtIndex2 >= texCoords.size()))
                throw string("Index out of bounds");
            if(nIndex2 < 0 || nIndex2 >= normals.size())
                throw string("Index out of bounds");

            Vector3 &vertex2 = vertices[vIndex2];
            Vector3 &normal2 = normals[nIndex2];
            GLfloat u2 = hasTexCoords ? texCoords[vtIndex2][0] : 0.0;
            GLfloat v2 = hasTexCoords ? texCoords[vtIndex2][1] : 0.0;

            Vertex modelVertex2{
                {vertex2[0], vertex2[1], vertex2[2]},
                {normal2[0], normal2[1], normal2[2]},
                {u2, v2}};
            modelData.push_back(modelVertex2);

            trianglesCount++;
        }
    }

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    GLuint bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, trianglesCount * 3 * sizeof(Vertex), &modelData[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

    if(hasTexCoords) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
