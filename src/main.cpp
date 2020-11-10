//
// Created by thijs on 11-08-20.
//
#include <GL/glew.h>

#include <iostream>
#include <set>

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
#include "objects/utils/PerlinNoiseHeightMap.h"
#include "objects/utils/PtrCompare.h"

class Vars {
private:
    TextureShader* textureShader;
    ColorShader* colorShader;
public:
    Window* window;
    std::multiset<Mesh*, PtrCompare<Mesh>> meshes;
    std::multiset<Interaction*, PtrCompare<Interaction>> interactions;
    std::multiset<PhysicsBody*, PtrCompare<PhysicsBody>> bodies;

    bool initVars() {
        // create player
        auto* player = new PhysicsBody(nullptr, {0, 10, 0}, {0, 0, 0});
        bodies.insert(player);

        // create window
        window = new Window(1000, 700, player, "Window");
        if (! *window) {
            return false;
        }

        // create manual inputs
        auto* mouse = new MouseInput(window, player, 10);
        auto* keyboard = new KeyboardInput(window, player, 5);
        interactions.insert(mouse);
        interactions.insert(keyboard);

        // create force interactions

        // create and compile shaders
        textureShader = new TextureShader();
        textureShader->loadShader("window/shader/TransformUVVertexShader.vertexshader",
                                  "window/shader/TextureFragmentShader.fragmentshader");

        // load texture
        textureShader->setAttr(Shader::getTextureFromDDS("uvtemplate.DDS"));
        textureShader->setUniformLocationAttr("textureSampler");
        textureShader->setUniformLocationMVP("MVP");

        colorShader = new ColorShader();
        colorShader->loadShader("window/shader/TransformColorVertexShader.vertexshader",
                                "window/shader/ColorFragmentShader.fragmentshader");

        colorShader->setUniformLocationMVP("MVP");

        // create floor
        auto* heightMap = new PerlinNoiseHeightMap(200.0f, 100.0f, glm::vec3{-50.0f}, 1.0f);
        Mesh* floor = new HeightMapMesh(window, colorShader, 0,1);
        auto* floorBuffer = heightMap->getMeshData();
        floor->setBuffer(floorBuffer);
        meshes.insert(floor);


        // create sphere
        auto* sphereBuffer = Mesh::CreateSphere(2.0f, -4.0f, 1.99f, 0.0f, 0.0f, 0.0f);
        Mesh* sphere = new ColorMesh(window, colorShader, 0, 1);
        sphere->setBuffer(sphereBuffer);
        meshes.insert(sphere);

        // create cube
        auto* cubeBuffer = Mesh::CreateCuboid(4.0f, 2.2f, 1.2f,
                                              0.0f, 10.9f, 0.0f,
                                              0.0f, 0.0f);
        Mesh* cube = new TextureMesh(window, textureShader, 0, 1);
        cube->setBuffer(cubeBuffer);
        auto* cubeBody = new PhysicsBody(cube, glm::vec3{0.0f, 10.9f, 0.0f});
        meshes.insert(cube);
        bodies.insert(cubeBody);

        // create second cube
        auto* cubeBuffer2 = Mesh::CreateCuboid(0.5f, 2.2f, 1.2f,
                                               4.0f, 0.9f, 0.0f,
                                               0.0f, 0.0f);
        Mesh* cube2 = new TextureMesh(window, textureShader, 0, 1);
        cube2->setBuffer(cubeBuffer2);
        meshes.insert(cube2);

        auto* floorInteraction = new FloorInteraction({player, cubeBody}, heightMap, 1.8f, -2);
        auto* gravity = new ConstantForce({player, cubeBody}, glm::vec3{0,-8.0f,0}, 3);

        interactions.insert(gravity);
        interactions.insert(floorInteraction);

        return true;
    }

    void deleteVars() {
        delete colorShader;
        delete textureShader;
        for (auto &interaction : interactions) {
            delete interaction;
        }
        for (auto &mesh : meshes) {
            delete mesh;
        }
        for (auto &body : bodies) {
            delete body;
        }
    }
};

int main() {
    // initialize variables
    Vars vars = Vars();
    bool success = vars.initVars();
    if (!success) {
        return 100;
    }
    auto* window = vars.window;
    auto meshes = vars.meshes;
    auto interactions = vars.interactions;
    auto bodies = vars.bodies;

    // main loop
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
    vars.deleteVars();
    delete window;

    return 0;
}