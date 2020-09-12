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
#include "objects/Object.h"

int main() {
    // create window
    auto* window = new Window(1000, 700, "Window");
    if (! *window) {
        return 100;
    }

    std::vector<Object*> objects;
    std::vector<Input*> inputs;

    // create inputs
    auto* mouse = new MouseInput(window);
    auto* keyboard = new KeyboardInput(window);
    inputs.push_back(mouse);
    inputs.push_back(keyboard);

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
    auto* floorObject = new Object(window, floor, colorShader);
    objects.push_back(floorObject);

    // create sphere
    auto* sphereBuffer = Mesh::CreateSphere(2.0f, -4.0f, 1.99f, 0.0f, 0.0f, 0.0f);
    Mesh* sphere = new ColorMesh(0, 1);
    sphere->setBuffer(sphereBuffer);
    auto* sphereObject = new Object(window, sphere, colorShader);
    objects.push_back(sphereObject);

    // create cube
    auto* cubeBuffer = Mesh::CreateCuboid(4.0f, 2.2f, 1.2f,
                                                                0.0f, 0.9f, 0.0f,
                                                                0.0f, 0.0f);
    Mesh* cube = new TextureMesh(0, 1);
    cube->setBuffer(cubeBuffer);
    auto* cubeObject = new Object(window, cube, textureShader);
    objects.push_back(cubeObject);

    // create second cube
    auto* cubeBuffer2 = Mesh::CreateCuboid(0.5f, 2.2f, 1.2f,
                                                                 4.0f, 0.9f, 0.0f,
                                                                 0.0f, 0.0f);
    Mesh* cube2 = new TextureMesh(0, 1);
    cube2->setBuffer(cubeBuffer2);
    auto* cube2Object = new Object(window, cube2, textureShader);
    objects.push_back(cube2Object);

    while (true) {
        window->updateFrameTime();
        window->clear();

        // update input
        for (auto &input : inputs) {
            input->update();
        }

        // update output
        window->update();

        // draw meshes
        for (auto &object : objects) {
            object->draw();
        }

        // swap buffers
        window->swapBuffers();

        glfwPollEvents();

        // check for exit button
        if (KeyboardInput::getExit(window)) {
            break;
        }
    }

    delete textureShader;
    delete keyboard;
    delete mouse;
    delete window;


    return 0;
}