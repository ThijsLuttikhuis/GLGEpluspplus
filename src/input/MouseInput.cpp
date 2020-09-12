//
// Created by thijs on 12-08-20.
//

#include "MouseInput.h"
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../window/Window.h"

MouseInput::MouseInput(Window* handle_) : Input(handle_) {
    auto* window = handle->getWindow();

    glfwPollEvents();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    handle->setCursorPosToCenter();
}

void MouseInput::update() {

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

