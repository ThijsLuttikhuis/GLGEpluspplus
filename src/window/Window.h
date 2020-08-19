//
// Created by thijs on 12-08-20.
//

#ifndef GLGEPLUSPLUS_WINDOW_H
#define GLGEPLUSPLUS_WINDOW_H


#include <string>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "Camera.h"

class Window {
private:
    int width;
    int height;

    std::string name;

    GLFWwindow* window;
    Camera* camera;

    double lastFrameTime;

public:

    Window(int width, int height, const std::string &name);
    ~Window();

    GLFWwindow* getWindow() const;
    Camera* getCamera() const;
    int getWidth() const;
    int getHeight() const;
    float getLastFrameTime() const;

    void clear(int flags);

    void setClearColor(const glm::vec4 &color);

    bool operator==(std::nullptr_t other) {
        return window == other;
    }

    void swapBuffers();
};


#endif //GLGEPLUSPLUS_WINDOW_H
