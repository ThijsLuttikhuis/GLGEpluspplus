//
// Created by thijs on 29-04-22.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "YamlReader.h"

YamlReader::YamlReader() {
    YamlHandlePhysicsBody yamlHandlePhysicsBody;
    auto glgeHandle = new YamlHandleGLGE;
    keyToFunc[".glge"] = glgeHandle;

    keyToFunc["physicsbody"] = new YamlHandlePhysicsBody();
    keyToFunc["window"] = new YamlHandleWindow();
    keyToFunc["mouseinput"] = new YamlHandleMouseInput();
    keyToFunc["keyboardinput"] = new YamlHandleKeyboardInput();
    keyToFunc["floorinteraction"] = new YamlHandleFloorInteraction();
    keyToFunc["constantforce"] = new YamlHandleConstantForce();

    keyToFunc["textureshader"] = new YamlHandleTextureShader();
    keyToFunc["colorshader"] = new YamlHandleColorShader();

    keyToFunc["perlinnoiseheightmap"] = new YamlHandlePerlinNoiseHeightMap();

    keyToFunc["cuboidmesh"] = new YamlHandleCuboidMesh();
    keyToFunc["heightmapmesh"] = new YamlHandleHeightMapMesh();

    keyToFunc["player"] = new YamlHandleGetByIDPhysicsBody(glgeHandle, stringCode::player);
    keyToFunc["iphysicsbody"] = new YamlHandleGetByIDPhysicsBody(glgeHandle, stringCode::iphysicsbody);
    keyToFunc["iwindow"] = new YamlHandleGetByIDWindow(glgeHandle, stringCode::iwindow);
    keyToFunc["imesh"] = new YamlHandleGetByIDMesh(glgeHandle, stringCode::imesh);
    keyToFunc["icolorshader"] = new YamlHandleGetByIDColorShader(glgeHandle, stringCode::icolorshader);
    keyToFunc["itextureshader"] = new YamlHandleGetByIDTextureShader(glgeHandle, stringCode::itextureshader);
    keyToFunc["iheightmap"] = new YamlHandleGetByIDHeightMap(glgeHandle, stringCode::iheightmap);

    keyToFunc["pos"] = new YamlHandleVec3(stringCode::pos);
    keyToFunc["vel"] = new YamlHandleVec3(stringCode::vel);
    keyToFunc["force"] = new YamlHandleVec3(stringCode::force);
    keyToFunc["corner"] = new YamlHandleVec3(stringCode::corner);
    keyToFunc["center"] = new YamlHandleVec3(stringCode::center);

    keyToFunc["x"] = new YamlHandleFloat(stringCode::x);
    keyToFunc["y"] = new YamlHandleFloat(stringCode::y);
    keyToFunc["z"] = new YamlHandleFloat(stringCode::z);
    keyToFunc["length"] = new YamlHandleFloat(stringCode::length);
    keyToFunc["width"] = new YamlHandleFloat(stringCode::width);
    keyToFunc["height"] = new YamlHandleFloat(stringCode::height);
    keyToFunc["squaresize"] = new YamlHandleFloat(stringCode::squaresize);
    keyToFunc["hangle"] = new YamlHandleFloat(stringCode::hangle);
    keyToFunc["vangle"] = new YamlHandleFloat(stringCode::vangle);

    keyToFunc["prio"] = new YamlHandleInt(stringCode::prio);
    keyToFunc["vertexlocation"] = new YamlHandleInt(stringCode::vertexlocation);
    keyToFunc["attrlocation"] = new YamlHandleInt(stringCode::attrlocation);

    keyToFunc["name"] = new YamlHandleString(stringCode::name);
    keyToFunc["id"] = new YamlHandleString(stringCode::id);
    keyToFunc["vertsh"] = new YamlHandleString(stringCode::vertsh);
    keyToFunc["fragsh"] = new YamlHandleString(stringCode::fragsh);
    keyToFunc["uvdds"] = new YamlHandleString(stringCode::uvdds);

}

void YamlReader::readFile(const std::string &fileName) {
    /// read file and put all data into a string

    std::ifstream file;
    file.open(fileName);
    if (!file) { // file couldn't be opened
        std::cerr << "[GameController::initialize] file could not be opened" << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string worldStr = buffer.str();
    worldStr.erase(std::remove_if(worldStr.begin(), worldStr.end(), isspace), worldStr.end());

    auto worldStrLength = worldStr.size();
    std::cout << worldStrLength << std::endl;

    std::string word;
    std::string obj;
    size_t i = 0;
    int colonCounter = 0;
    int colonCounterMax = 5;

    std::vector<YamlHandle*> objectHandle(colonCounterMax, nullptr);
    while (i < worldStrLength) {
        size_t posColon = worldStr.find(':', i);
        size_t posSemi = worldStr.find(';', i);

        if (posSemi < posColon) {
            word = worldStr.substr(i, posSemi - i);
            std::cout << "\t" << posSemi << " ; " << word << std::endl;
            i = posSemi + 1;

            if (!word.empty()) {
                objectHandle[colonCounter] = keyToFunc.find(word) != keyToFunc.end() ? keyToFunc[word] : nullptr;
            }

            if (objectHandle[colonCounter]) {
                objectHandle[colonCounter]->handle();

                objectHandle[colonCounter - 1]->handle(objectHandle[colonCounter]);

            } else {
                objectHandle[colonCounter - 1]->handle(word);
            }

            objectHandle[colonCounter] = nullptr;
            colonCounter--;
        } else {
            word = worldStr.substr(i, posColon - i);
            std::cout << "\t" << posColon << " : " << word << std::endl;
            i = posColon + 1;

            if (objectHandle[colonCounter]) {
                objectHandle[colonCounter - 1]->handle(objectHandle[colonCounter]);
            }
            objectHandle[colonCounter] = keyToFunc.find(word) != keyToFunc.end() ? keyToFunc[word] : nullptr;
            colonCounter++;
        }
    }

    if (!objectHandle[0]) {
        std::cerr << "[YamlReader::readFile] no object handle remaining" << std::endl;
    }

    glgeHandle = objectHandle[0];
}




