//
// Created by thijs on 12-08-20.
//

#ifndef GLGEPLUSPLUS_MOUSEINPUT_H
#define GLGEPLUSPLUS_MOUSEINPUT_H

#include "Input.h"

class Window;

class MouseInput : public Input {
private:
    float mouseSpeed = 0.005f;
public:
    MouseInput(Window* window, PhysicsBody* body);
    void update() override;
};


#endif //GLGEPLUSPLUS_MOUSEINPUT_H
