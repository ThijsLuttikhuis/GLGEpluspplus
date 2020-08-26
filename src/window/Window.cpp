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
    glm::vec3 position = glm::vec3( 0, 0, 5 );
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float fieldOfView = 90.0f;
    camera = new Camera(position, horizontalAngle, verticalAngle, fieldOfView);

    // set dark grey background
    glm::vec4 clearColor = {0.1f, 0.1f, 0.1f, 0.0f};
    setClearColor(clearColor);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Generate vertex array
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
}

Window::~Window() {
    glDeleteVertexArrays(1, &vertexArrayID);
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

glm::vec2 Window::getCursorPos() {
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

void Window::setCursorPosToCenter() {
    glfwSetCursorPos(window, width/2.0, height/2.0);
}

void Window::setCursorPos(glm::vec2 mousePos) {
    glfwSetCursorPos(window, (double)mousePos.x, (double)mousePos.y);
}

glm::vec2 Window::getCursorPosRelativeToCenter() {
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    double xrel = width/2.0 - xpos;
    double yrel = height/2.0 - ypos;
    return {xrel, yrel};
}

