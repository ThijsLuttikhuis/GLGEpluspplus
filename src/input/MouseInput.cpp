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
            glfwSetCursorPos(window, 1024.0 / 2, 768.0 / 2);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;

        case 0x0002:
            // Set the mouse at the center of the screen
            glfwPollEvents();
            glfwSetCursorPos(window, 1024.0 / 2, 768.0 / 2);
        case 0x0004:
        case 0x0008:
        default:
            glfwPollEvents();
            glfwSetCursorPos(window, 1024.0 / 2, 768.0 / 2);
            break;
    }
}

void MouseInput::update(Window* handle) {

    auto width = static_cast<double>(handle->getWidth());

    auto height = static_cast<double>(handle->getHeight());

    auto* window = handle->getWindow();

    auto* camera = handle->getCamera();
    auto hAngle = camera->getHorizontalAngle();
    auto vAngle = camera->getVerticalAngle();

    // Get mouse position
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, width/2, height/2);

    hAngle += mouseSpeed * (width/2 - xpos);
    vAngle += mouseSpeed * (height/2 - ypos);

    camera->setHorizontalAngle(hAngle);
    camera->setVerticalAngle(vAngle);
}

