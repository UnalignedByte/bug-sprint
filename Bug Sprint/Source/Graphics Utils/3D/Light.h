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
    Light(GLfloat viewWidth, GLfloat viewHeight, GLfloat cutOff = -1.0f);

    Color getColor() const;
    void setColor(const Color &color);

    GLfloat getAmbientIntensity() const;
    void setAmbientIntensity(GLfloat ambientIntensity);
    GLfloat getDiffuseIntensity() const;
    void setDiffuseIntensity(GLfloat diffuseIntensity);
    GLfloat getSpecularIntensity() const;
    void setSpecularIntensity(GLfloat specularIntensity);

    Vector3 getDirection() const;
    Vector3 getTarget() const;
    void setTarget(const Vector3 &target);

    virtual void addRenderPass(std::shared_ptr<RenderPass> renderPass);
    virtual void removeRenderPass(std::shared_ptr<RenderPass> renderPass);

    virtual void addShadowRenderPass(std::shared_ptr<RenderPass> renderPass);
    virtual void removeShadowRenderPass(std::shared_ptr<RenderPass> renderPass);

    void updateLight();
    void updateShadow();

protected:
    static GLint lightsCount;
    GLint lightIndex;

    Type type;
    Color color{1.0, 1.0, 1.0, 1.0};
    GLfloat ambientIntensity{0.2};
    GLfloat diffuseIntensity{1.0};
    GLfloat specularIntensity{1.0};

    GLfloat viewWidth;
    GLfloat viewHeight;
    GLfloat fov{60.0};
    GLfloat zNear{0.01};
    GLfloat zFar{100.0};

    Vector3 target{0.0, 0.0, 1.0};

    GLfloat cutOff;

    std::set<std::shared_ptr<RenderPass>> renderPasses;
    std::set<std::shared_ptr<RenderPass>> shadowRenderPasses;
};

#endif
