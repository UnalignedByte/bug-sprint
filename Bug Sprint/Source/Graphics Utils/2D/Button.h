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
    Button(const std::string &upImageFileName, const std::string &downImageFileName = "",
           const std::string &inactiveImageFileName = "");

    virtual void setTitle(const std::string &title, const std::string &fontFileName, GLfloat fontSize,
                          const Color &fontColor);

    virtual GLfloat getRange() const;
    void setRange(GLfloat range);

    GLsizei getTrianglesCount() const override;
    virtual void setIsInactive(bool isInactive);
    State getState() const;

    void updateInput(const Input &input) override;
    void update(float timeInterval) override;
    void draw(std::shared_ptr<ShaderProgram> shaderProgram) override;

protected:
    std::unique_ptr<Sprite> upSprite;
    std::unique_ptr<Sprite> downSprite;
    std::unique_ptr<Sprite> inactiveSprite;
    std::unique_ptr<Sprite> titleSprite;

    GLfloat range{-1};

    State state{StateUp};
    int touchId{-1};

protected:
    bool isTouchInside(const Input::Touch &touch);
};

#endif
