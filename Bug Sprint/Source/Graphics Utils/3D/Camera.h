//
//  Camera.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 19/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "Instance3D.h"

#include <memory>
#include <set>
#include "RenderPass.h"
#include "Vector.h"


class Camera: public Instance3D
{
public:
    enum Type {
        TypeOrtographic,
        TypePerspective
    };

public:
    Camera(GLfloat width, GLfloat height, GLfloat depth, GLfloat fieldOfView = -1.0);

    Type getType() const;
    GLfloat getWidth() const;
    GLfloat getHeight() const;
    GLfloat getDepth() const;
    GLfloat getFieldOfView() const;
    Vector3 getTarget() const;
    void setTarget(const Vector3 &target);

    virtual void addRenderPass(std::shared_ptr<RenderPass> renderPass);
    virtual void removeRenderPass(std::shared_ptr<RenderPass> renderPass);

    void updateCamera();

protected:
    Type type;

    GLfloat width;
    GLfloat height;
    GLfloat aspectRatio;
    GLfloat zNear{0.01};
    GLfloat zFar;
    GLfloat fieldOfView;

    Vector3 target;

    std::set<std::shared_ptr<RenderPass>> renderPasses;
};

#endif
