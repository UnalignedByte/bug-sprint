//
// Created by Rafal Grodzinski on 26/11/2016.
//

#include "Button.h"

#include "SystemUtils.h"

using namespace std;


Button::Button(shared_ptr<ShaderProgram> shaderProgram, const string &upImageFileName,
               const string &downImageFileName, const string &inactiveImageFileName) :
    shaderProgram(shaderProgram), upSprite(new Sprite(upImageFileName, shaderProgram))
{
    width = upSprite->getWidth();
    height = upSprite->getHeight();

    if(!downImageFileName.empty()) {
        downSprite = make_unique<Sprite>(downImageFileName, shaderProgram);

        if(downSprite->getWidth() > width)
            width = downSprite->getWidth();

        if(downSprite->getHeight() > height)
            height = downSprite->getHeight();
    }

    if(!inactiveImageFileName.empty()) {
        inactiveSprite = make_unique<Sprite>(inactiveImageFileName, shaderProgram);

        if(inactiveSprite->getWidth() > width)
            width = inactiveSprite->getWidth();

        if(inactiveSprite->getHeight() > height)
            height = inactiveSprite->getHeight();
    }
}


void Button::setTitle(const string &title, const string &fontFileName, GLfloat fontSize,
                      const Color &fontColor)
{
    titleSprite = make_unique<Sprite>(title, fontFileName, fontSize, fontColor, shaderProgram);
}


shared_ptr<ShaderProgram> Button::getShader() const
{
    return shaderProgram;
}


GLfloat Button::getWidth() const
{
    return width;
}


GLfloat Button::getHeight() const
{
    return height;
}


GLsizei Button::getTrianglesCount() const
{
    GLsizei count = upSprite->getTrianglesCount();

    if(titleSprite != nullptr)
        count += titleSprite->getTrianglesCount();

    return count;
}


void Button::setIsInactive(bool isInactive)
{
    state = StateInactive;
}


void Button::updateInput(double timeInterval, const Input &input)
{
    if(state == StateInactive)
        return;

    GLfloat left = position[0] - width/2.0;
    GLfloat right = position[0] + width/2.0;
    GLfloat top = position[1] + height/2.0;
    GLfloat bottom = position[1] - height/2.0;

    bool isInside = input.x >= left && input.x <= right && input.y >= bottom && input.y <= top;
    if((input.state == Input::StateDown || input.state == Input::StateMoved) && isInside) {
        state = StateDown;
    } else {
        state = StateUp;
    }
}


void Button::update(double timeInterval)
{
    if(upSprite != nullptr) {
        upSprite->position = position;
        upSprite->scale = scale;
        upSprite->rotation = rotation;

        upSprite->update(timeInterval);
    }

    if(downSprite != nullptr) {
        downSprite->position = position;
        downSprite->scale = scale;
        downSprite->rotation = rotation;

        downSprite->update(timeInterval);
    }

    if(inactiveSprite != nullptr) {
        inactiveSprite->position = position;
        inactiveSprite->scale = scale;
        inactiveSprite->rotation = rotation;

        inactiveSprite->update(timeInterval);
    }
}


void Button::draw()
{
    if(state == StateInactive && inactiveSprite != nullptr) {
        inactiveSprite->draw();
    } else if(state == StateDown && downSprite != nullptr) {
        downSprite->draw();
    } else {
        upSprite->draw();
    }

    if(titleSprite != nullptr)
        titleSprite->draw();
}
