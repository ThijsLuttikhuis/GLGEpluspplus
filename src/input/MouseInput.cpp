//
// Created by thijs on 12-08-20.
//

#include "MouseInput.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../window/Window.h"

MouseInput::MouseInput(Window* handle, int mode_) : mode(mode_) {
    auto* window = handle->getWindow();
    switch (mode) {
        case 0x0001:
            // Set the mouse at the center of the screen
            glfwPollEvents();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;

        case 0x0002:
            // Set the mouse at the center of the screen
            glfwPollEvents();
            break;
        case 0x0004:
        case 0x0008:
        default:
            glfwPollEvents();
            break;
    }

    handle->setCursorPosToCenter();
}

void MouseInput::update(Window* handle) {


    auto* camera = handle->getCamera();
    auto hAngle = camera->getHorizontalAngle();
    auto vAngle = camera->getVerticalAngle();

    auto relativeMousePos = handle->getCursorPosRelativeToCenter();
    handle->setCursorPosToCenter();

    // Set vertical/horizontal angle
    hAngle += mouseSpeed * relativeMousePos.x;
    vAngle += mouseSpeed * relativeMousePos.y;

    // Bound vertical angle
    float delta = 0.01f;
    float maxVerticalAngle = M_PI_2 - delta;

    vAngle = vAngle < -maxVerticalAngle ? -maxVerticalAngle :
             vAngle > maxVerticalAngle ? maxVerticalAngle :
             vAngle;

    camera->setHorizontalAngle(hAngle);
    camera->setVerticalAngle(vAngle);
}

