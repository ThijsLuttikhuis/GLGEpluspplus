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
#include "TEMP.h"
#include "objects/Mesh.h"
#include "window/Shader.h"


int main() {
    // create window
    auto* window = new Window(1024, 768, "Window");
    if (! *window) {
        return 100;
    }

    // create inputs
    auto* mouse = new MouseInput(window, GLGE_MOUSE_CURSOR_FPS);
    auto* keyboard = new KeyboardInput(window, GLGE_STICKY_KEYS);

    // create and compile shaders
    auto* shader = new Shader();
    shader->loadShader("TransformVertexShader.vertexshader",
                      "TextureFragmentShader.fragmentshader");

    // load texture
    shader->setTextureFromDDS("uvtemplate.DDS");
    shader->setUniformLocationTexture("textureSampler");

    // load matrix
    shader->setUniformLocationMVP("MVP");

    // create cube


    auto cubeBuffer = Mesh::CreateCuboid(4.0f, 2.0f, 1.2f,
                                                                0.0f, 0.0f, 0.0f,
                                                                0.0f, 0.0f);
    auto* cube = new Mesh(0, 1);
    cube->setBuffer(cubeBuffer);

    // create second
    auto cubeBuffer2 = Mesh::CreateCuboid(0.5f, 2.0f, 1.2f,
                                                                 4.0f, 2.0f, 0.0f,
                                                                 0.0f, 0.0f);
    auto* cube2 = new Mesh(0, 1);
    cube2->setBuffer(cubeBuffer2);


    while (true) {
        window->updateFrameTime();
        window->clear();

        // use shader
        shader->useShader();

        // update input
        mouse->update(window);
        keyboard->update(window);

        // update output
        window->update();
        shader->update(window);

        // draw output
        cube->draw();
        cube2->draw();

        // swap buffers
        window->swapBuffers();

        glfwPollEvents();

        // check for exit button
        if (keyboard->getExit(window)) {
            break;
        }
    }

    delete shader;
    delete keyboard;
    delete mouse;
    delete window;


    return 0;
}