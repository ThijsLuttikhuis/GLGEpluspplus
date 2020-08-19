//
// Created by thijs on 11-08-20.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "input/MouseInput.h"
#include "input/KeyboardInput.h"
#include "window/Window.h"


int main() {
    // create window
    auto* window = new Window(1024, 768, "Window");

    // create inputs
    auto* mouse = new MouseInput(window, GLGE_MOUSE_FPS);
    auto* keyboard = new KeyboardInput(window, GLGE_STICKY_KEYS);

    // set dark grey background
    glm::vec4 clearColor = {0.1f, 0.1f, 0.1f, 0.0f};
    window->setClearColor(clearColor);

    while (true) {
        // Clear screen
        window->clear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        window->swapBuffers();

        glfwPollEvents();


        mouse->update(window);
        keyboard->update(window);

        // Check for exit button
        if (keyboard->getExit(window)) {
            break;
        }

    }

    // Exit procedure
    delete window;

    return 0;

}