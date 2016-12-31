//
//  DebugSprite.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 29/12/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "DebugSprite.h"
#include "SystemUtils.h"

using namespace std;



DebugSprite::DebugSprite(GLint textureId, GLfloat width, GLfloat height) :
    textureId(textureId)
{
    SystemUtils::Point size = SystemUtils::sizeForViewSize(width, height);

    this->width = size.x;
    this->height = size.y;

    GLfloat halfWidth = this->width/2.0;
    GLfloat halfHeight = this->height/2.0;

    /*vertices[0] = {{-halfWidth, -halfHeight}, {0.0f, 1.0f}};
    vertices[1] = {{+halfWidth, +halfHeight}, {1.0f, 0.0f}};
    vertices[2] = {{-halfWidth, +halfHeight}, {0.0f, 0.0f}};
    vertices[3] = {{-halfWidth, -halfHeight}, {0.0f, 1.0f}};
    vertices[4] = {{+halfWidth, -halfHeight}, {1.0f, 1.0f}};
    vertices[5] = {{+halfWidth, +halfHeight}, {1.0f, 0.0f}};*/

    vertices[0] = -halfWidth;
    vertices[1] = -halfHeight;
    vertices[2] = +halfWidth;
    vertices[3] = +halfHeight;
    vertices[4] = -halfWidth;
    vertices[5] = +halfHeight;
    vertices[6] = -halfWidth;
    vertices[7] = -halfHeight;
    vertices[8] = +halfWidth;
    vertices[9] = -halfHeight;
    vertices[10] = +halfWidth;
    vertices[11] = +halfHeight;

    texCoords[0] = 0.0f;
    texCoords[1] = 1.0f;
    texCoords[2] = 1.0f;
    texCoords[3] = 0.0f;
    texCoords[4] = 0.0f;
    texCoords[5] = 0.0f;
    texCoords[6] = 0.0f;
    texCoords[7] = 1.0f;
    texCoords[8] = 1.0f;
    texCoords[9] = 1.0f;
    texCoords[10] = 1.0f;
    texCoords[11] = 0.0f;

}

void DebugSprite::draw(shared_ptr<ShaderProgram> shaderProgram)
{
    shaderProgram->use();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLint modelMatrixId = glGetUniformLocation(shaderProgram->getId(), "modelMatrix");
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, modelMatrix.getData());

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);
    GLint diffuseSamplerId = glGetUniformLocation(shaderProgram->getId(), "diffuseSampler");
    glUniform1i(diffuseSamplerId, 2);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, NULL, vertices);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, NULL, texCoords);// + offsetof(Vertex, texCoords));
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
