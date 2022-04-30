//
// Created by thijs on 28-04-22.
//

#ifndef GLGEPLUSPLUS_GAMECONTROLLER_H
#define GLGEPLUSPLUS_GAMECONTROLLER_H

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

class GameController {
private:
    TextureShader* textureShader = nullptr;
    ColorShader* colorShader = nullptr;

    Window* window = nullptr;

    std::multiset<Mesh*, PtrCompare<Mesh>> meshes{};
    std::multiset<Interaction*, PtrCompare<Interaction>> interactions{};
    std::multiset<PhysicsBody*, PtrCompare<PhysicsBody>> bodies{};

public:
    GameController() = default;

    void initialize();
    void update();
    void close();

    [[nodiscard]] Window* getWindow();
};


#endif //GLGEPLUSPLUS_GAMECONTROLLER_H
