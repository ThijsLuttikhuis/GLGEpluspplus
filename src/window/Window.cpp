//
// Created by thijs on 12-08-20.
//

#include <GL/glew.h>
#include <iostream>
#include "Window.h"
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Window::Window(int width_, int height_, const std::string &name) : width(width_), height(height_) {

    // initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW." << std::endl;
        getchar();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to open GLFW window." << std::endl;
        getchar();
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        getchar();
        glfwTerminate();
    }

    // Initialize Camera
    camera = new Camera();
}

Window::~Window() {
    glfwTerminate();
}



void Window::clear(int flags) {
    glClear(flags);
}

void Window::setClearColor(const glm::vec4 &color) {
    glClearColor(color[0], color[1],color[2],color[3]);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

double Window::getLastFrameTime() const {
    return lastFrameTime;
}

GLFWwindow* Window::getWindow() const {
    return window;
}

Camera* Window::getCamera() const {
    return camera;
}

void Window::updateFrameTime() {
    auto t = glfwGetTime();
    lastFrameTime = t - time;
    time = t;
    std::cout << lastFrameTime * 1000 << " ms" << std::endl;
}

void Window::update() {

    auto w = static_cast<float>(width);
    auto h = static_cast<float>(height);
    auto aspectRatio = w/h;
    auto near = 0.1f;
    auto far = 100.0f;

    camera->updateMatrices(aspectRatio, near, far);
    
}
