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


int main() {
    // create window
    auto* window = new Window(1024, 768, "Window");
    if (! *window) {
        return 100;
    }

    // create inputs
    auto* mouse = new MouseInput(window, GLGE_MOUSE_CURSOR_FPS);
    auto* keyboard = new KeyboardInput(window, GLGE_STICKY_KEYS);

    // set dark grey background
    glm::vec4 clearColor = {0.1f, 0.1f, 0.1f, 0.0f};
    window->setClearColor(clearColor);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = TEMP::LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Load the texture
    GLuint Texture = TEMP::loadDDS("uvtemplate.DDS");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
          -1.0f,-1.0f,-1.0f,
          -1.0f,-1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f,-1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f, 1.0f,-1.0f,
          1.0f,-1.0f, 1.0f,
          -1.0f,-1.0f,-1.0f,
          1.0f,-1.0f,-1.0f,
          1.0f, 1.0f,-1.0f,
          1.0f,-1.0f,-1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f,-1.0f,
          1.0f,-1.0f, 1.0f,
          -1.0f,-1.0f, 1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f, 1.0f, 1.0f,
          -1.0f,-1.0f, 1.0f,
          1.0f,-1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f,-1.0f,-1.0f,
          1.0f, 1.0f,-1.0f,
          1.0f,-1.0f,-1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f,-1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f,-1.0f,
          -1.0f, 1.0f,-1.0f,
          1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f,-1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f,-1.0f, 1.0f
    };

    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const GLfloat g_uv_buffer_data[] = {
          0.000059f, 0.000004f,
          0.000103f, 0.336048f,
          0.335973f, 0.335903f,
          1.000023f, 0.000013f,
          0.667979f, 0.335851f,
          0.999958f, 0.336064f,
          0.667979f, 0.335851f,
          0.336024f, 0.671877f,
          0.667969f, 0.671889f,
          1.000023f, 0.000013f,
          0.668104f, 0.000013f,
          0.667979f, 0.335851f,
          0.000059f, 0.000004f,
          0.335973f, 0.335903f,
          0.336098f, 0.000071f,
          0.667979f, 0.335851f,
          0.335973f, 0.335903f,
          0.336024f, 0.671877f,
          1.000004f, 0.671847f,
          0.999958f, 0.336064f,
          0.667979f, 0.335851f,
          0.668104f, 0.000013f,
          0.335973f, 0.335903f,
          0.667979f, 0.335851f,
          0.335973f, 0.335903f,
          0.668104f, 0.000013f,
          0.336098f, 0.000071f,
          0.000103f, 0.336048f,
          0.000004f, 0.671870f,
          0.336024f, 0.671877f,
          0.000103f, 0.336048f,
          0.336024f, 0.671877f,
          0.335973f, 0.335903f,
          0.667969f, 0.671889f,
          1.000004f, 0.671847f,
          0.667979f, 0.335851f
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    //glfwSwapInterval(0);

    while (true) {
        window->updateFrameTime();
        window->clear((uint)GL_COLOR_BUFFER_BIT | (uint)GL_DEPTH_BUFFER_BIT);

        // Use shader
        glUseProgram(programID);

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

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
              0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
              3,                  // size
              GL_FLOAT,           // type
              GL_FALSE,           // normalized?
              0,                  // stride
              nullptr             // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
              1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
              2,                                // size : U+V => 2
              GL_FLOAT,                         // type
              GL_FALSE,                         // normalized?
              0,                                // stride
              nullptr                           // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        window->swapBuffers();

        glfwPollEvents();

        // Check for exit button
        if (keyboard->getExit(window)) {
            break;
        }
    }

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}