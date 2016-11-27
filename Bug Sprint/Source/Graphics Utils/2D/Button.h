//
// Created by Rafal Grodzinski on 26/11/2016.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "Instance2D.h"

#include <string>
#include <memory>
#include "Color.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Types.h"


class Button: public Instance2D
{
public:
    Button(std::shared_ptr<ShaderProgram> shaderProgram, const std::string &upImageFileName,
           const std::string &downImageFileName = "", const std::string &inactiveImageFileName = "");

    virtual void setTitle(const std::string &title, const std::string &fontFileName, GLfloat fontSize,
                          const Color &fontColor);

    virtual std::shared_ptr<ShaderProgram> getShader() const;
    virtual GLfloat getWidth() const;
    virtual GLfloat getHeight() const;
    GLsizei getTrianglesCount() const override;
    virtual void setIsInactive(bool isInactive);

    virtual void updateInput(double timeinterval, const Input &input);
    void update(double timeInterval) override;
    void draw() override;

protected:
    enum State {
        StateUp,
        StateDown,
        StateInactive
    };

protected:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::unique_ptr<Sprite> upSprite;
    std::unique_ptr<Sprite> downSprite;
    std::unique_ptr<Sprite> inactiveSprite;
    std::unique_ptr<Sprite> titleSprite;

    GLfloat width;
    GLfloat height;

    State state{StateUp};
};

#endif
