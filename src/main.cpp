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

    // create cube triangles
    const std::vector<glm::vec3> cubeBuffer = Mesh::CreateCuboid(4.0f, 2.0f, 1.2f,
                                                                0.0f, 0.0f, 0.0f,
                                                                0.0f, 0.0f);

    // Two UV coordinates for each vertex. They were created with Blender.
    const std::vector<glm::vec2> g_uv_buffer_data = {
          {0.000f, 0.000f},
          {0.000f, 0.333f},
          {0.333f, 0.333f},
          {1.000f, 0.000f},
          {0.667f, 0.333f},
          {0.000f, 0.333f},
          {0.667f, 0.333f},
          {0.333f, 0.667f},
          {0.667f, 0.667f},
          {1.000f, 0.000f},
          {0.667f, 0.000f},
          {0.667f, 0.333f},
          {0.000f, 0.000f},
          {0.333f, 0.333f},
          {0.333f, 0.000f},
          {0.667f, 0.333f},
          {0.333f, 0.333f},
          {0.333f, 0.667f},
          {1.000f, 0.667f},
          {0.000f, 0.333f},
          {0.667f, 0.333f},
          {0.667f, 0.000f},
          {0.333f, 0.333f},
          {0.667f, 0.333f},
          {0.333f, 0.333f},
          {0.667f, 0.000f},
          {0.333f, 0.000f},
          {0.000f, 0.333f},
          {0.000f, 0.667f},
          {0.333f, 0.667f},
          {0.000f, 0.333f},
          {0.333f, 0.667f},
          {0.333f, 0.333f},
          {0.667f, 0.667f},
          {1.000f, 0.667f},
          {0.667f, 0.333f}
    };

    auto* cube = new Mesh(0, 1);
    cube->setBuffer(cubeBuffer, g_uv_buffer_data);

    while (true) {
        window->updateFrameTime();
        window->clear((uint)GL_COLOR_BUFFER_BIT | (uint)GL_DEPTH_BUFFER_BIT);

        // Use shader
        glUseProgram(shader->getProgramID());

        mouse->update(window);
        keyboard->update(window);

        window->update();

        shader->update(window);

        cube->draw();


        // Swap buffers
        window->swapBuffers();

        glfwPollEvents();

        // Check for exit button
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