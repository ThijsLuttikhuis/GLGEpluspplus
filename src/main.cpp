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

    // Create and compile our GLSL program from the shaders
    auto* shader = new Shader();
    shader->loadShader("TransformVertexShader.vertexshader",
                      "TextureFragmentShader.fragmentshader");

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(shader->getProgramID(), "MVP");

    // Load the texture
    GLuint Texture = TEMP::loadDDS("uvtemplate.DDS");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(shader->getProgramID(), "myTextureSampler");

    const std::vector<glm::vec3> g_vertex_buffer_data = {
          {-1.0f,-1.0f,-1.0f},
          {-1.0f,-1.0f, 1.0f},
          {-1.0f, 1.0f, 1.0f},
          {1.0f, 1.0f,-1.0f},
          {-1.0f,-1.0f,-1.0f},
          {-1.0f, 1.0f,-1.0f},
          {1.0f,-1.0f, 1.0f},
          {-1.0f,-1.0f,-1.0f},
          {1.0f,-1.0f,-1.0f},
          {1.0f, 1.0f,-1.0f},
          {1.0f,-1.0f,-1.0f},
          {-1.0f,-1.0f,-1.0f},
          {-1.0f,-1.0f,-1.0f},
          {-1.0f, 1.0f, 1.0f},
          {-1.0f, 1.0f,-1.0f},
          {1.0f,-1.0f, 1.0f},
          {-1.0f,-1.0f, 1.0f},
          {-1.0f,-1.0f,-1.0f},
          {-1.0f, 1.0f, 1.0f},
          {-1.0f,-1.0f, 1.0f},
          {1.0f,-1.0f, 1.0f},
          {1.0f, 1.0f, 1.0f},
          {1.0f,-1.0f,-1.0f},
          {1.0f, 1.0f,-1.0f},
          {1.0f,-1.0f,-1.0f},
          {1.0f, 1.0f, 1.0f},
          {1.0f,-1.0f, 1.0f},
          {1.0f, 1.0f, 1.0f},
          {1.0f, 1.0f,-1.0f},
          {-1.0f, 1.0f,-1.0f},
          {1.0f, 1.0f, 1.0f},
          {-1.0f, 1.0f,-1.0f},
          {-1.0f, 1.0f, 1.0f},
          {1.0f, 1.0f, 1.0f},
          {-1.0f, 1.0f, 1.0f},
          {1.0f,-1.0f, 1.0f}
    };

    // Two UV coordinates for each vertex. They were created with Blender.
    const std::vector<glm::vec2> g_uv_buffer_data = {
          {0.000059f, 0.000004f},
          {0.000103f, 0.336048f},
          {0.335973f, 0.335903f},
          {1.000023f, 0.000013f},
          {0.667979f, 0.335851f},
          {0.999958f, 0.336064f},
          {0.667979f, 0.335851f},
          {0.336024f, 0.671877f},
          {0.667969f, 0.671889f},
          {1.000023f, 0.000013f},
          {0.668104f, 0.000013f},
          {0.667979f, 0.335851f},
          {0.000059f, 0.000004f},
          {0.335973f, 0.335903f},
          {0.336098f, 0.000071f},
          {0.667979f, 0.335851f},
          {0.335973f, 0.335903f},
          {0.336024f, 0.671877f},
          {1.000004f, 0.671847f},
          {0.999958f, 0.336064f},
          {0.667979f, 0.335851f},
          {0.668104f, 0.000013f},
          {0.335973f, 0.335903f},
          {0.667979f, 0.335851f},
          {0.335973f, 0.335903f},
          {0.668104f, 0.000013f},
          {0.336098f, 0.000071f},
          {0.000103f, 0.336048f},
          {0.000004f, 0.671870f},
          {0.336024f, 0.671877f},
          {0.000103f, 0.336048f},
          {0.336024f, 0.671877f},
          {0.335973f, 0.335903f},
          {0.667969f, 0.671889f},
          {1.000004f, 0.671847f},
          {0.667979f, 0.335851f}
    };

    auto* cube = new Mesh(0, 1);

    cube->setBuffer(g_vertex_buffer_data, g_uv_buffer_data);

    while (true) {
        window->updateFrameTime();
        window->clear((uint)GL_COLOR_BUFFER_BIT | (uint)GL_DEPTH_BUFFER_BIT);

        // Use shader
        glUseProgram(shader->getProgramID());

        mouse->update(window);
        keyboard->update(window);
        window->update();

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &window->getCamera()->getMVP()[0][0]);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);

        cube->enableAttributeBuffer();

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        cube->disableAttributeBuffer();

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

    // Cleanup VBO and shader
    glDeleteTextures(1, &TextureID);

    return 0;
}