//
// Created by Rafal Grodzinski on 26/11/2016.
//

#include "Button.h"

#include "SystemUtils.h"

using namespace std;


Button::Button(const string &upImageFileName, const string &downImageFileName, const string &inactiveImageFileName) :
    upSprite(new Sprite(upImageFileName))
{
    width = upSprite->getWidth();
    height = upSprite->getHeight();

    if(!downImageFileName.empty()) {
        downSprite = make_unique<Sprite>(downImageFileName);

        if(downSprite->getWidth() > width)
            width = downSprite->getWidth();

        if(downSprite->getHeight() > height)
            height = downSprite->getHeight();
    }

    if(!inactiveImageFileName.empty()) {
        inactiveSprite = make_unique<Sprite>(inactiveImageFileName);

        if(inactiveSprite->getWidth() > width)
            width = inactiveSprite->getWidth();

        if(inactiveSprite->getHeight() > height)
            height = inactiveSprite->getHeight();
    }
}


void Button::setTitle(const string &title, const string &fontFileName, GLfloat fontSize,
                      const Color &fontColor)
{
    titleSprite = make_unique<Sprite>(title, fontFileName, fontSize, fontColor);
}


GLfloat Button::getRange() const
{
    return range;
}


void Button::setRange(GLfloat range)
{
    this->range = range;
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


Button::State Button::getState() const
{
    return state;
}


void Button::updateInput(const Input &input)
{
    if(state == StateInactive || input.touches.size() == 0)
        return;

    Input::Touch touch;
    bool isInside = false;

    auto touchIt = input.touches.find(touchId);
    if(touchIt != input.touches.end()) {
        touch = (*touchIt).second;
        isInside = isTouchInside(touch);
    } else {
        for(auto &touchIt : input.touches) {
            if(isTouchInside(touchIt.second)) {
                touchId = touchIt.first;
                touch = touchIt.second;
                isInside = true;
            }
        }
    }

    if(touch.state == Input::Touch::StateInvalid)
        return;

    // Is touch up inside?
    if(state == StateDown && touch.state == Input::Touch::StateUp && isInside && pressedCallback != nullptr)
        pressedCallback();

    if((state == StateUp && touch.state == Input::Touch::StateDown && isInside) ||
       (state == StateDown && touch.state != Input::Touch::StateUp && isInside)) {
        state = StateDown;
    } else {
        state = StateUp;
        touchId = -1;
    }
}


bool Button::isTouchInside(const Input::Touch &touch)
{
    GLfloat left = position[0] - width/2.0;
    GLfloat right = position[0] + width/2.0;
    GLfloat top = position[1] + height/2.0;
    GLfloat bottom = position[1] - height/2.0;

    bool isInside;
    if(range > 0.0) {
        GLfloat distanceSquared = (touch.x - position[0]) * (touch.x - position[0]) +
        (touch.y - position[1]) * (touch.y - position[1]);

        isInside = range*range >= distanceSquared;
    } else {
        isInside = touch.x >= left && touch.x <= right && touch.y >= bottom && touch.y <= top;
    }

    return isInside;
}


void Button::update(float timeInterval)
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


void Button::draw(shared_ptr<ShaderProgram> shaderProgram)
{
    Drawable2D::draw(shaderProgram);

    if(state == StateInactive && inactiveSprite != nullptr) {
        inactiveSprite->draw(shaderProgram);
    } else if(state == StateDown && downSprite != nullptr) {
        downSprite->draw(shaderProgram);
    } else {
        upSprite->draw(shaderProgram);
    }

    if(titleSprite != nullptr)
        titleSprite->draw(shaderProgram);
}
