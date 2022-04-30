//
// Created by thijs on 28-04-22.
//

#include <sstream>
#include <algorithm>
#include "GameController.h"
#include "readwrite/YamlReader.h"

Window* GameController::getWindow() {
    return window;
}

void GameController::initialize() {
    YamlReader yamlReader;
    yamlReader.readFile("./readwrite/world.glge");

    auto data = yamlReader.getData();

    meshes = data->meshes;
    bodies = data->bodies;
    interactions = data->interactions;
    textureShader = data->textureShader;
    colorShader = data->colorShader;
    window = data->window;


//
//    /// create player
//    auto* player = new PhysicsBody("id", nullptr, {10, 10, 10}, {0, 0, 0});
//    bodies.insert(player);
//
//    /// create window
//    window = new Window("id", 1366, 768, player, "Window");
//    if (!*window) {
//        std::cerr << "error creating window" << std::endl;
//        exit(-1);
//    }
//
//    /// create manual inputs
//    auto* mouse = new MouseInput("id", window, player, 10);
//    auto* keyboard = new KeyboardInput("id", window, player, 5);
//    interactions.insert(mouse);
//    interactions.insert(keyboard);
//
//    /// create force interactions
//
//    /// create and compile shaders
//    textureShader = new TextureShader();
//    textureShader->loadShader("window/shader/TransformUVVertexShader.vertexshader",
//                              "window/shader/TextureFragmentShader.fragmentshader");
//
//    /// load texture
//    textureShader->setAttr(Shader::getTextureFromDDS("uvtemplate.DDS"));
//    textureShader->setUniformLocationAttr("textureSampler");
//    textureShader->setUniformLocationMVP("MVP");
//
//    colorShader = new ColorShader();
//    colorShader->loadShader("window/shader/TransformColorVertexShader.vertexshader",
//                            "window/shader/ColorFragmentShader.fragmentshader");
//
//    colorShader->setUniformLocationMVP("MVP");
//
//    /// create floor
//    auto* heightMap = new PerlinNoiseHeightMap("id", 200.0f, 100.0f, glm::vec3{-50.0f}, 1.0f);
//    Mesh* floor = new HeightMapMesh("id", window, colorShader, 0, 1);
//    auto* floorBuffer = heightMap->getMeshData();
//    floor->setBuffer(floorBuffer);
//    meshes.insert(floor);
//
//
//    /// create sphere
//    auto* sphereBuffer = Mesh::CreateSphere(2.0f, -4.0f, 1.99f, 0.0f, 0.0f, 0.0f);
//    Mesh* sphere = new ColorMesh("id", window, colorShader, 0, 1);
//    sphere->setBuffer(sphereBuffer);
//    meshes.insert(sphere);
//
//    /// create cube
//    auto* cubeBuffer = Mesh::CreateCuboid(3.0f, 2.2f, 4.2f,
//                                          0.0f, 0.0f, 0.0f,
//                                          0.0f, 0.0f);
//    Mesh* cube = new TextureMesh("id", window, textureShader, 0, 1);
//    cube->setBuffer(cubeBuffer);
//    auto* cubeBody = new PhysicsBody("id", cube, glm::vec3{0.0f, 50.9f, 0.0f});
//    meshes.insert(cube);
//    bodies.insert(cubeBody);
//
//    /// create second cube
//    auto* cubeBuffer2 = Mesh::CreateCuboid(0.5f, 2.2f, 1.2f,
//                                           4.0f, 0.9f, 0.0f,
//                                           0.0f, 0.0f);
//    Mesh* cube2 = new TextureMesh("id", window, textureShader, 0, 1);
//    cube2->setBuffer(cubeBuffer2);
//    meshes.insert(cube2);
//
////    auto* planeBuffer = Mesh::CreatePlane(100.0, 100.0, 0.0, 0.0, -50.0, 1.0f);
////    Mesh* plane = new TextureMesh(window, textureShader, 0, 1);
////    plane->setBuffer(planeBuffer);
////    meshes.insert(plane);
//
////    auto* boxFloorMap = new HeightMap(20.0f, 20.0f, glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f);
////
////    Mesh* boxFloor = new HeightMapMesh(window, colorShader, 0, 1);
////    auto* boxFloorBuffer = boxFloorMap->getMeshData();
////    boxFloor->setBuffer(boxFloorBuffer);
////    meshes.insert(boxFloor);
//
//
//    auto* floorInteraction = new FloorInteraction("id", {player, cubeBody}, heightMap, 1.8f, -2);
//    auto* gravity = new ConstantForce("id", {player, cubeBody}, glm::vec3{0, -8.0f, 0}, 3);
//
//    interactions.insert(gravity);
//    interactions.insert(floorInteraction);
}

void GameController::update() {
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

}

void GameController::close() {
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

