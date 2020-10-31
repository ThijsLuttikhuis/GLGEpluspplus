//
// Created by thijs on 12-08-20.
//

#include "KeyboardInput.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>


KeyboardInput::KeyboardInput(Window* handle_, PhysicsBody* body) : Input(handle_, {body}) {
    // Capture keys
    auto* window = handle->getWindow();

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void KeyboardInput::update() {

    auto* window = handle->getWindow();

    auto* camera = handle->getCamera();
    auto force = bodies[0]->getForce();  //camera->getPosition();
    auto vel = bodies[0]->getVel();
    auto dVel = glm::vec3(0.0f, 0.0f, 0.0f);
    auto forwards = camera->getHorizonForwards();
    auto right = camera->getRight();

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        dVel += glm::normalize(forwards);
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        dVel -= glm::normalize(forwards);
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        dVel += glm::normalize(right);
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        dVel -= glm::normalize(right);
    }
    // Up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        dVel += glm::normalize(glm::cross(right, forwards));
    }
    // Down
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        dVel -= glm::normalize(glm::cross(right, forwards));
    }

    if (glm::length(dVel) > 0.01f) {
        dVel = glm::normalize(dVel) * moveSpeed;
    }

    camera->setPosition(bodies[0]->getPos());
    bodies[0]->setForce(dVel);
}

bool KeyboardInput::getExit(Window* handle_) {
    auto* window = handle_->getWindow();

    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
           glfwWindowShouldClose(window) != 0;
}
