//
//  Light.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 20/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef LIGHT_H
#define LIGHT_H

#include "Instance3D.h"

#include <memory>
#include "RenderPass.h"
#include "Vector.h"
#include "Color.h"


class Light: public Instance3D
{
public:
    enum Type {
        TypeUnused = 0,
        TypeDirectional = 1,
        TypeSpot = 2,
        TypePoint = 3,
    };

public:
    Light(GLint viewWidth, GLint viewHeight, GLfloat cutOff = -1.0f, GLfloat innerCutOff = -1.0f);

    Type getType() const;
    GLint getLightIndex() const;
    bool getShouldCastShadow() const;

    Color getColor() const;
    void setColor(const Color &color);
    GLfloat getAmbientIntensity() const;
    void setAmbientIntensity(GLfloat ambientIntensity);
    GLfloat getDiffuseIntensity() const;
    void setDiffuseIntensity(GLfloat diffuseIntensity);
    GLfloat getSpecularIntensity() const;
    void setSpecularIntensity(GLfloat specularIntensity);

    Vector3 getDirection() const;
    void setDirection(Vector3 direction);
    Vector3 getWorldDirection() const;
    Vector3 getWorldTarget() const;
    void setWorldTarget(Vector3 worldTarget);

    void updateLight(std::shared_ptr<ShaderProgram> shaderProgram);
    void updateShadow(std::shared_ptr<ShaderProgram> shaderProgram);

    void useFramebuffer();
    void useShadowTexture(std::shared_ptr<ShaderProgram> shaderProgram);

protected:
    static GLint lightsCount;
    GLint lightIndex;

    Type type;
    bool shouldCastShadow{true};

    Color color{1.0, 1.0, 1.0, 1.0};
    GLfloat ambientIntensity{0.2};
    GLfloat diffuseIntensity{1.0};
    GLfloat specularIntensity{1.0};

    GLint viewWidth;
    GLint viewHeight;
    GLfloat fov{60.0};
    GLfloat zNear{0.01};
    GLfloat zFar{100.0};

    Vector3 direction{0.0, 0.0, 1.0};
    Vector3 worldTarget{0.0, 0.0, 0.0};

    GLfloat cutOff;
    GLfloat innerCutOff;

    GLuint framebuffer;
    static GLuint texture;
};

#endif
