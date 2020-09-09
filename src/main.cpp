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

#include "window/shader/Shader.h"
#include "window/shader/TextureShader.h"
#include "window/shader/ColorShader.h"

#include "window/mesh/Mesh.h"
#include "window/mesh/TextureMesh.h"
#include "window/mesh/ColorMesh.h"

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
    auto* textureShader = new TextureShader();
    textureShader->loadShader("window/shader/TransformUVVertexShader.vertexshader",
                              "window/shader/TextureFragmentShader.fragmentshader");

    // load texture
    textureShader->setAttr(Shader::getTextureFromDDS("uvtemplate.DDS"));
    textureShader->setUniformLocationAttr("textureSampler");
    textureShader->setUniformLocationMVP("MVP");

    auto* colorShader = new ColorShader();
    colorShader->loadShader("window/shader/TransformColorVertexShader.vertexshader",
                            "window/shader/ColorFragmentShader.fragmentshader");

    textureShader->setUniformLocationMVP("MVP");

    // create floor
    auto* floorBuffer = Mesh::CreatePlane(20.0f, 20.0f, 0.0f, 0.0f, 0.0f);
    Mesh* floor = new ColorMesh(0,1);
    floor->setBuffer(floorBuffer);

    // create sphere
    auto* sphereBuffer = Mesh::CreateSphere(2.0f, -4.0f, 1.99f, 0.0f, 0.0f, 0.0f);
    Mesh* sphere = new ColorMesh(0, 1);
    sphere->setBuffer(sphereBuffer);

    // create cube
    auto* cubeBuffer = Mesh::CreateCuboid(4.0f, 2.2f, 1.2f,
                                                                0.0f, 0.9f, 0.0f,
                                                                0.0f, 0.0f);
    Mesh* cube = new TextureMesh(0, 1);
    cube->setBuffer(cubeBuffer);

    // create second cube
    auto* cubeBuffer2 = Mesh::CreateCuboid(0.5f, 2.2f, 1.2f,
                                                                 4.0f, 0.9f, 0.0f,
                                                                 0.0f, 0.0f);
    Mesh* cube2 = new TextureMesh(0, 1);
    cube2->setBuffer(cubeBuffer2);


    while (true) {
        window->updateFrameTime();
        window->clear();

        // update input
        mouse->update(window);
        keyboard->update(window);

        // update output
        window->update();

        // use color shader
        colorShader->useShader();
        colorShader->update(window);
        // draw sphere
        sphere->draw();
        floor->draw();

        // use texture shader
        textureShader->useShader();
        textureShader->update(window);
        // draw cubes
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

    delete textureShader;
    delete keyboard;
    delete mouse;
    delete window;


    return 0;
}