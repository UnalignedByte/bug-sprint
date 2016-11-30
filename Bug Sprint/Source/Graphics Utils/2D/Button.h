//
// Created by Rafal Grodzinski on 26/11/2016.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "Instance2D.h"

#include <string>
#include <memory>
#include <functional>
#include "Color.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Types.h"


class Button: public Instance2D
{
public:
    enum State {
        StateUp,
        StateDown,
        StateInactive
    };

public:
    std::function<void()> pressedCallback{nullptr};

public:
    Button(std::shared_ptr<ShaderProgram> shaderProgram, const std::string &upImageFileName,
           const std::string &downImageFileName = "", const std::string &inactiveImageFileName = "");

    virtual void setTitle(const std::string &title, const std::string &fontFileName, GLfloat fontSize,
                          const Color &fontColor);

    virtual std::shared_ptr<ShaderProgram> getShader() const;
    virtual GLfloat getWidth() const;
    virtual GLfloat getHeight() const;
    virtual GLfloat getRange() const;
    void setRange(GLfloat range);
    GLsizei getTrianglesCount() const override;
    virtual void setIsInactive(bool isInactive);
    State getState() const;

    virtual void updateInput(double timeinterval, const Input &input);
    void update(double timeInterval) override;
    void draw() override;

protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::unique_ptr<Sprite> upSprite;
    std::unique_ptr<Sprite> downSprite;
    std::unique_ptr<Sprite> inactiveSprite;
    std::unique_ptr<Sprite> titleSprite;

    GLfloat width;
    GLfloat height;

    GLfloat range{-1};

    State state{StateUp};
};

#endif
