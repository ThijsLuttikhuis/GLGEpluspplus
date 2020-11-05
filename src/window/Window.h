//
// Created by thijs on 12-08-20.
//

#ifndef GLGEPLUSPLUS_WINDOW_H
#define GLGEPLUSPLUS_WINDOW_H


#include <string>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

class PhysicsBody;
class Camera;

class Window {
private:
    int width;
    int height;

    std::string name;

    GLFWwindow* window;
    Camera* camera;

    double lastFrameTime = 0.0;
    double time = 0.0;

    uint vertexArrayID;

public:

    Window(int width, int height, PhysicsBody* player, const std::string &name);

    ~Window();

    GLFWwindow* getWindow() const;

    Camera* getCamera() const;

    int getWidth() const;

    int getHeight() const;

    float getLastFrameTime() const;

    void clear(int flags);
    void clear();

    void setClearColor(const glm::vec4 &color);

    bool operator !() {
        return !window;
    }

    void swapBuffers();

    void update();

    void updateFrameTime();

    glm::vec2 getCursorPos();

    void setCursorPos(glm::vec2 tvec2);

    void setCursorPosToCenter();

    glm::vec2 getCursorPosRelativeToCenter();
};


#endif //GLGEPLUSPLUS_WINDOW_H
