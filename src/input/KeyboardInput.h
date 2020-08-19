//
// Created by thijs on 12-08-20.
//

#ifndef GLGEPLUSPLUS_KEYBOARDINPUT_H
#define GLGEPLUSPLUS_KEYBOARDINPUT_H

#include "../window/Window.h"

#define GLGE_STICKY_KEYS GLFW_STICKY_KEYS


class KeyboardInput {
private:
    int mode;
    float moveSpeed = 5.0f; // 3 units / second

public:

    KeyboardInput(Window* handle, int mode_);

    void update(Window* handle);

    bool getExit(Window* handle);
};


#endif //GLGEPLUSPLUS_KEYBOARDINPUT_H
