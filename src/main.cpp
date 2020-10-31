//
// Created by thijs on 11-08-20.
//
#include <GL/glew.h>

#include <iostream>

#include "window/Window.h"

#include "input/MouseInput.h"
#include "input/KeyboardInput.h"

#include "window/shader/Shader.h"
#include "window/shader/TextureShader.h"
#include "window/shader/ColorShader.h"

#include "window/mesh/Mesh.h"
#include "window/mesh/TextureMesh.h"
#include "window/mesh/ColorMesh.h"

#include "objects/Interactions/Interaction.h"
#include "objects/Interactions/ConstantForce.h"
#include "window/mesh/HeightMapMesh.h"
#include "objects/utils/HeightMap.h"
#include "objects/Interactions/FloorInteraction.h"

int main() {
    // create window
    auto* window = new Window(1000, 700, "Window");
    if (! *window) {
        return 100;
    }

    // initialize vectors
    std::vector<Mesh*> meshes;
    std::vector<Interaction*> interactions;
    std::vector<PhysicsBody*> bodies;

    // create player
    auto* player = new PhysicsBody(nullptr, {0, 10, 0}, {0, 0, 0});
    bodies.push_back(player);

    // create manual inputs
    auto* mouse = new MouseInput(window, player);
    auto* keyboard = new KeyboardInput(window, player);
    interactions.push_back(mouse);
    interactions.push_back(keyboard);

    // create force interactions
    auto* gravity = new ConstantForce({player}, glm::vec3{0,-8.0f,0});
    interactions.push_back(gravity);

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
    auto* heightMap = new HeightMap(200.0f, 100.0f, glm::vec3{-50.0f}, 1.0f);
    Mesh* floor = new HeightMapMesh(window, colorShader, 0,1);
    auto* floorBuffer = heightMap->getMeshData();
    floor->setBuffer(floorBuffer);
    meshes.push_back(floor);

    auto* floorInteraction = new FloorInteraction({player}, heightMap, 1.8f);
    interactions.push_back(floorInteraction);

    // create sphere
    auto* sphereBuffer = Mesh::CreateSphere(2.0f, -4.0f, 1.99f, 0.0f, 0.0f, 0.0f);
    Mesh* sphere = new ColorMesh(window, colorShader, 0, 1);
    sphere->setBuffer(sphereBuffer);
    meshes.push_back(sphere);

    // create cube
    auto* cubeBuffer = Mesh::CreateCuboid(4.0f, 2.2f, 1.2f,
                                                                0.0f, 0.9f, 0.0f,
                                                                0.0f, 0.0f);
    Mesh* cube = new TextureMesh(window, textureShader, 0, 1);
    cube->setBuffer(cubeBuffer);
    meshes.push_back(cube);

    // create second cube
    auto* cubeBuffer2 = Mesh::CreateCuboid(0.5f, 2.2f, 1.2f,
                                                                 4.0f, 0.9f, 0.0f,
                                                                 0.0f, 0.0f);
    Mesh* cube2 = new TextureMesh(window, textureShader, 0, 1);
    cube2->setBuffer(cubeBuffer2);
    meshes.push_back(cube2);

    while (true) {
        window->updateFrameTime();
        window->clear();

        float dt = window->getLastFrameTime();

        // update inputs, physics and interactions
        for (auto &interaction : interactions) {
            interaction->update();
        }

        // update bodies
        for (auto &body : bodies) {
            body->update(dt);
        }

        // update output
        window->update();

        // draw meshes
        for (auto &mesh : meshes) {
            mesh->draw();
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