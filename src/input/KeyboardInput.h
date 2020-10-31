//
// Created by thijs on 12-08-20.
//

#ifndef GLGEPLUSPLUS_KEYBOARDINPUT_H
#define GLGEPLUSPLUS_KEYBOARDINPUT_H

#include "../window/Window.h"
#include "Input.h"

class KeyboardInput : public Input {
private:
    float moveSpeed = 12.0f;
public:
    KeyboardInput(Window* handle, PhysicsBody* body);

    void update() override;

    static bool getExit(Window* handle);
};


#endif //GLGEPLUSPLUS_KEYBOARDINPUT_H
