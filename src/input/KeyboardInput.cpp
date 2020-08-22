//
// Created by thijs on 12-08-20.
//

#include "KeyboardInput.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>


KeyboardInput::KeyboardInput(Window* handle, int mode_) : mode(mode_) {
    // Capture keys
    auto* window = handle->getWindow();
    auto width = static_cast<double>(handle->getWidth());
    auto height = static_cast<double>(handle->getHeight());

    switch (mode) {
        case 0x0001:
            // Set the mouse at the center of the screen
            glfwPollEvents();
            glfwSetCursorPos(window, width / 2, height / 2);
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            break;

        case 0x0002:
        case 0x0004:
        case 0x0008:
        default:
            glfwPollEvents();
            glfwSetCursorPos(window, width / 2, height / 2);
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            break;
    }
}

void KeyboardInput::update(Window* handle) {

    auto dt = static_cast<float>(handle->getLastFrameTime());

    auto* window = handle->getWindow();

    auto* camera = handle->getCamera();
    auto pos = camera->getPosition();
    auto dir = camera->getDirection();
    auto right = camera->getRight();

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        pos += dir * dt * moveSpeed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        pos -= dir * dt * moveSpeed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pos += right * dt * moveSpeed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pos -= right * dt * moveSpeed;
    }
    camera->setPosition(pos);
}

bool KeyboardInput::getExit(Window* handle) {
    auto* window = handle->getWindow();

    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
            glfwWindowShouldClose(window) != 0;
}
