//
// Created by thijs on 12-08-20.
//

#include "KeyboardInput.h"
#include <GLFW/glfw3.h>
#include <cmath>


KeyboardInput::KeyboardInput(Window* handle, int mode_) : mode(mode_) {
    // Capture keys

    auto* window = handle->getWindow();
    switch (mode) {
        case 0x0001:
            // Set the mouse at the center of the screen
            glfwPollEvents();
            glfwSetCursorPos(window, 1024.0 / 2, 768.0 / 2);
            break;

        case 0x0002:
        case 0x0004:
        case 0x0008:
        default:
            glfwPollEvents();
            glfwSetCursorPos(window, 1024.0 / 2, 768.0 / 2);
            break;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void KeyboardInput::update(Window* handle) {

    float dt = handle->getLastFrameTime();

    auto* window = handle->getWindow();

    auto* camera = handle->getCamera();
    auto pos = camera->getPosition();
    auto hAngle = camera->getHorizontalAngle();
    auto vAngle = camera->getVerticalAngle();

    glm::vec3 direction = {cos(vAngle) * sin(hAngle),
                           sin(vAngle),
                           cos(vAngle) * cos(hAngle)};
    glm::vec3 right = glm::vec3{sin(hAngle - M_PI_2),
                                0,
                                cos(hAngle - M_PI_2)};


    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        pos += direction * dt * moveSpeed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        pos -= direction * dt * moveSpeed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        pos += right * dt * moveSpeed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        pos -= right * dt * moveSpeed;
    }


}

bool KeyboardInput::getExit(Window* handle) {
    auto* window = handle->getWindow();

    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
            glfwWindowShouldClose(window) != 0;

}
