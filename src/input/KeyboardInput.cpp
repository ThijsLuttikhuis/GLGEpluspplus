//
// Created by thijs on 12-08-20.
//

#include "KeyboardInput.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>


KeyboardInput::KeyboardInput(Window* handle_) : Input(handle_) {
    // Capture keys
    auto* window = handle->getWindow();
    auto width = static_cast<double>(handle->getWidth());
    auto height = static_cast<double>(handle->getHeight());

            // Set the mouse at the center of the screen
            glfwPollEvents();
            glfwSetCursorPos(window, width / 2, height / 2);
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

}

void KeyboardInput::update() {

    auto dt = static_cast<float>(handle->getLastFrameTime());

    auto* window = handle->getWindow();

    auto* camera = handle->getCamera();
    auto pos = camera->getPosition();
    auto vel = glm::vec3(0.0f, 0.0f, 0.0f);
    auto forwards = camera->getHorizonForwards();
    auto right = camera->getRight();

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vel += glm::normalize(forwards);
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vel -= glm::normalize(forwards);
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vel += glm::normalize(right);
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vel -= glm::normalize(right);
    }
    // Up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        vel += glm::normalize(glm::cross(right, forwards));
    }
    // Down
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        vel -= glm::normalize(glm::cross(right, forwards));
    }

    if (glm::length(vel) > 0.01f) {
        vel = glm::normalize(vel) * moveSpeed;
    }
    pos += vel * dt;

    camera->setPosition(pos);
}

bool KeyboardInput::getExit(Window* handle_) {
    auto* window = handle_->getWindow();

    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
            glfwWindowShouldClose(window) != 0;
}
