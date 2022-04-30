//
// Created by thijs on 29-04-22.
//

#ifndef GLGEPLUSPLUS_YAMLREADER_H
#define GLGEPLUSPLUS_YAMLREADER_H


#include <set>
#include "../window/mesh/Mesh.h"
#include "../objects/Interactions/Interaction.h"
#include "../objects/utils/PtrCompare.h"
#include "../window/shader/TextureShader.h"
#include "../window/shader/ColorShader.h"
#include "../input/MouseInput.h"
#include "../input/KeyboardInput.h"
#include "../objects/utils/PerlinNoiseHeightMap.h"
#include "../window/mesh/TextureMesh.h"
#include "../objects/Interactions/FloorInteraction.h"
#include "../objects/Interactions/ConstantForce.h"

enum stringCode {
    glge,                      // 0
    physicsbody,               // 1
    window,                    // 2
    mouseinput,                // 3
    keyboardinput,             // 4
    textureshader,             // 5
    colorshader,               // 6
    perlinnoiseheightmap,      // 7
    cuboidmesh,                // 8
    floorinteraction,          // 9
    constantforce,             // 10
    id,                        // 11
    pos,                       // 12
    vel,                       // 13
    corner,                    // 14
    hangle,                    // 15
    vangle,                    // 16
    center,                    // 17
    x,                         // 18
    y,                         // 19
    z,                         // 20
    length,                    // 21
    width,                     // 22
    height,                    // 23
    squaresize,                // 24
    name,                      // 25
    prio,                      // 26
    vertsh,                    // 27
    fragsh,                    // 28
    uvdds,                     // 29
    player,                    // 30
    imesh,                     // 31
    iwindow,                   // 32
    icolorshader,              // 33
    itextureshader,            // 34
    iphysicsbody,              // 35
    vertexlocation,            // 36
    attrlocation,              // 37
    iheightmap,                 // 38
    heightmapmesh,
    force
};

class YamlData {
public:
    std::multiset<Mesh*, PtrCompare<Mesh>> meshes{};
    std::multiset<Interaction*, PtrCompare<Interaction>> interactions{};
    std::multiset<PhysicsBody*, PtrCompare<PhysicsBody>> bodies{};

    TextureShader* textureShader = nullptr;
    ColorShader* colorShader = nullptr;

    Window* window = nullptr;

    YamlData() = default;
};

class YamlHandle {
protected:
    stringCode type;

public:
    explicit YamlHandle(stringCode type) : type(type) {};

    const stringCode &getType() const {
        return type;
    }

    virtual void* getFeature() {};

    virtual void handle() {};

    virtual void handle(YamlHandle* yamlHandle) {
        std::cerr << "[YamlHandle::handle(YamlHandle*)] function not implemented";
        exit(5);
    };

    virtual void handle(std::string value) {
        std::cerr << "[YamlHandle::handle(std::string)] function not implemented";
        exit(5);
    };

};

class YamlHandleGLGE : public YamlHandle {
    YamlData* yamlData;

//    std::multiset<Mesh*, PtrCompare<Mesh>> meshes{};
//    std::multiset<Interaction*, PtrCompare<Interaction>> interactions{};
//    std::multiset<PhysicsBody*, PtrCompare<PhysicsBody>> bodies{};
//
    std::vector<HeightMap*> heightMaps{};
//
//    TextureShader* textureShader = nullptr;
//    ColorShader* colorShader = nullptr;
//
//    Window* window = nullptr;

public:
    YamlHandleGLGE() : YamlHandle(stringCode::glge) {
        yamlData = new YamlData;
    };

    void handle(YamlHandle* yamlHandle) override {
        std::cout << "yh.glge adding object" << std::endl;

        switch (yamlHandle->getType()) {
            case stringCode::physicsbody:
                yamlData->bodies.insert((PhysicsBody*) yamlHandle->getFeature());
                break;
            case stringCode::window:
                yamlData->window = (Window*) yamlHandle->getFeature();
                break;
            case stringCode::mouseinput:
                yamlData->interactions.insert((MouseInput*) yamlHandle->getFeature());
                break;
            case stringCode::keyboardinput:
                yamlData->interactions.insert((KeyboardInput*) yamlHandle->getFeature());
                break;
            case stringCode::textureshader:
                yamlData->textureShader = (TextureShader*) yamlHandle->getFeature();
                break;
            case stringCode::colorshader:
                yamlData->colorShader = (ColorShader*) yamlHandle->getFeature();
                break;
            case stringCode::perlinnoiseheightmap:
                heightMaps.push_back((HeightMap*) yamlHandle->getFeature());
                break;
            case stringCode::cuboidmesh:
                yamlData->meshes.insert((Mesh*) yamlHandle->getFeature());
                break;
            case stringCode::heightmapmesh:
                yamlData->meshes.insert((Mesh*) yamlHandle->getFeature());
                break;
            case stringCode::constantforce:
                yamlData->interactions.insert((ConstantForce*) yamlHandle->getFeature());
                break;
            case stringCode::floorinteraction:
                yamlData->interactions.insert((FloorInteraction*) yamlHandle->getFeature());
                break;
            default:
                std::cerr << "[YamlHandleGLGE] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    PhysicsBody* getPhysicsBodyByID(const std::string &str) {
        for (auto &body : yamlData->bodies) {
            if (body->getID() == str) {
                return body;
            }
        }
        std::cerr << "[YamlHandleGLGE::getPhysicsBodyByID] id does not exist" << std::endl;
        return nullptr;
    }

    Window* getWindowByID(const std::string &str) {
        if (yamlData->window->getID() == str) {
            return yamlData->window;
        }
        std::cerr << "[YamlHandleGLGE::getPhysicsBodyByID] id does not exist" << std::endl;
        return nullptr;
    }

    Mesh* getMeshByID(const std::string &str) {
        for (auto &mesh : yamlData->meshes) {
            if (mesh->getID() == str) {
                return mesh;
            }
        }
        std::cerr << "[YamlHandleGLGE::getMeshByID] id does not exist" << std::endl;
        return nullptr;
    }

    TextureShader* getTextureShaderByID(const std::string &str) {
        return yamlData->textureShader;
    }

    ColorShader* getColorShaderByID(const std::string &str) {
        return yamlData->colorShader;
    }

    HeightMap* getHeightMapByID(const std::string &str) {
        for (auto &heightmap : heightMaps) {
            if (heightmap->getID() == str) {
                return heightmap;
            }
        }
        std::cerr << "[YamlHandleGLGE::getHeightMapByID] id does not exist" << std::endl;
        return nullptr;
    }

    void* getFeature() override {
        return (void*) yamlData;
    };
};

class YamlHandlePhysicsBody : public YamlHandle {
    PhysicsBody* feature{};

    std::string id;
    Mesh* mesh{};
    glm::vec3 pos;
    glm::vec3 vel;
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    int priority = 0;

public:
    YamlHandlePhysicsBody() : YamlHandle(stringCode::physicsbody) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::imesh:
                mesh = (Mesh*) yamlHandle->getFeature();
                break;
            case stringCode::pos:
                pos = *(glm::vec3*) yamlHandle->getFeature();
                break;
            case stringCode::vel:
                vel = *(glm::vec3*) yamlHandle->getFeature();
                break;
            case stringCode::hangle:
                horizontalAngle = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::vangle:
                verticalAngle = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::prio:
                priority = *(int*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandlePhysicsBody] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        feature = new PhysicsBody(id, mesh, pos, vel, horizontalAngle, verticalAngle, priority);
        return (void*) feature;
    };
};

class YamlHandleWindow : public YamlHandle {
    Window* feature{};

    std::string id;
    int width = 0;
    int height = 0;
    PhysicsBody* player = nullptr;
    std::string windowName;

public:
    YamlHandleWindow() : YamlHandle(stringCode::window) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::width:
                width = static_cast<int>( *(float*) yamlHandle->getFeature());
                break;
            case stringCode::height:
                height = static_cast<int>( *(float*) yamlHandle->getFeature());
                break;
            case stringCode::player:
                player = (PhysicsBody*) yamlHandle->getFeature();
                break;
            case stringCode::name:
                windowName = *(std::string*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleWindow] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        feature = new Window(id, width, height, player, windowName);
        return (void*) feature;
    };
};


class YamlHandlePerlinNoiseHeightMap : public YamlHandle {
    std::string id;
    float length = 0.0f;
    float width = 0.0f;
    glm::vec3 corner{};
    float squareSize = 0.0f;

public:
    YamlHandlePerlinNoiseHeightMap() : YamlHandle(stringCode::perlinnoiseheightmap) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::length:
                length = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::width:
                width = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::corner:
                corner = *(glm::vec3*) yamlHandle->getFeature();
                break;
            case stringCode::squaresize:
                squareSize = *(float*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandlePerlinNoiseHeightMap] unsupported feature: " << yamlHandle->getType()
                          << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        auto* heightMap = new PerlinNoiseHeightMap(id, length, width, corner, squareSize);
        return (void*) heightMap;
    };
};

class YamlHandleHeightMapMesh : public YamlHandle {
    std::string id;
    HeightMap* heightMap{};
    Window* window{};
    ColorShader* colorShader{};
    int vertexLocation = 0;
    int attrLocation = 1;

public:
    YamlHandleHeightMapMesh() : YamlHandle(stringCode::heightmapmesh) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::iheightmap:
                heightMap = (HeightMap*) yamlHandle->getFeature();
                break;
            case stringCode::iwindow:
                window = (Window*) yamlHandle->getFeature();
                break;
            case stringCode::icolorshader:
                colorShader = (ColorShader*) yamlHandle->getFeature();
                break;
            case stringCode::vertexlocation:
                vertexLocation = *(int*) yamlHandle->getFeature();
                break;
            case stringCode::attrlocation:
                attrLocation = *(int*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandlePerlinNoiseHeightMap] unsupported feature: " << yamlHandle->getType()
                          << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        Mesh* heightMapMesh = new HeightMapMesh(id, window, colorShader, vertexLocation, attrLocation);
        auto* meshData = heightMap->getMeshData();
        heightMapMesh->setBuffer(meshData);
        return (void*) heightMapMesh;
    };
};


class YamlHandleCuboidMesh : public YamlHandle {
    std::string id;
    float length = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    glm::vec3 center{};
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    Window* window{};
    TextureShader* textureShader{};
    int vertexLocation = 0;
    int attrLocation = 1;

public:
    YamlHandleCuboidMesh() : YamlHandle(stringCode::cuboidmesh) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::hangle:
                horizontalAngle = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::vangle:
                verticalAngle = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::length:
                length = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::width:
                width = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::height:
                height = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::center:
                center = *(glm::vec3*) yamlHandle->getFeature();
                break;
            case stringCode::iwindow:
                window = (Window*) yamlHandle->getFeature();
                break;
            case stringCode::itextureshader:
                textureShader = (TextureShader*) yamlHandle->getFeature();
                break;
            case stringCode::vertexlocation:
                vertexLocation = *(int*) yamlHandle->getFeature();
                break;
            case stringCode::attrlocation:
                attrLocation = *(int*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleCuboidMesh] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        auto* cubeBuffer = Mesh::CreateCuboid(length, height, width,
                                              center.x, center.y, center.z,
                                              horizontalAngle, verticalAngle);
        Mesh* cube = new TextureMesh(id, window, textureShader, vertexLocation, attrLocation);
        cube->setBuffer(cubeBuffer);
        return cube;
    };
};


class YamlHandleMouseInput : public YamlHandle {
    MouseInput* feature{};

    std::string id;
    PhysicsBody* player{};
    Window* window{};
    int priority = 0;

public:
    YamlHandleMouseInput() : YamlHandle(stringCode::mouseinput) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::prio:
                priority = *(int*) yamlHandle->getFeature();
                break;
            case stringCode::player:
                player = (PhysicsBody*) yamlHandle->getFeature();
                break;
            case stringCode::iwindow:
                window = (Window*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleMouseInput] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        feature = new MouseInput(id, window, player, priority);
        return (void*) feature;
    };
};


class YamlHandleKeyboardInput : public YamlHandle {
    KeyboardInput* feature{};

    std::string id;
    PhysicsBody* player{};
    Window* window{};
    int priority = 0;

public:
    YamlHandleKeyboardInput() : YamlHandle(stringCode::mouseinput) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::prio:
                priority = *(int*) yamlHandle->getFeature();
                break;
            case stringCode::player:
                player = (PhysicsBody*) yamlHandle->getFeature();
                break;
            case stringCode::iwindow:
                window = (Window*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleKeyboardInput] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        feature = new KeyboardInput(id, window, player, priority);
        return (void*) feature;
    };
};


class YamlHandleFloorInteraction : public YamlHandle {

    std::string id;
    std::vector<PhysicsBody*> bodies{};
    HeightMap* heightMap{};
    float height = 0;
    int priority = 0;

public:
    YamlHandleFloorInteraction() : YamlHandle(stringCode::floorinteraction) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::prio:
                priority = *(int*) yamlHandle->getFeature();
                break;
            case stringCode::iphysicsbody:
                bodies.push_back((PhysicsBody*) yamlHandle->getFeature());
                break;
            case stringCode::height:
                height = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::iheightmap:
                heightMap = (HeightMap*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleMouseInput] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        auto* floorInteraction = new FloorInteraction(id, bodies, heightMap, height, -2);

        return (void*) floorInteraction;
    };
};


class YamlHandleConstantForce : public YamlHandle {

    std::string id;
    std::vector<PhysicsBody*> bodies{};
    glm::vec3 force{};
    int priority = 0;

public:
    YamlHandleConstantForce() : YamlHandle(stringCode::constantforce) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::prio:
                priority = *(int*) yamlHandle->getFeature();
                break;
            case stringCode::iphysicsbody:
                bodies.push_back((PhysicsBody*) yamlHandle->getFeature());
                break;
            case stringCode::force:
                force = *(glm::vec3*) yamlHandle->getFeature();
                break;

            default:
                std::cerr << "[YamlHandleMouseInput] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        auto* constantForce = new ConstantForce(id, bodies, force, -2);

        return (void*) constantForce;
    };
};

class YamlHandleTextureShader : public YamlHandle {
    std::string id;
    std::string vertexShaderStr;
    std::string fragmentShaderStr;
    std::string uvddsStr;

public:
    YamlHandleTextureShader() : YamlHandle(stringCode::textureshader) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::vertsh:
                vertexShaderStr = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::fragsh:
                fragmentShaderStr = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::uvdds:
                uvddsStr = *(std::string*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleTextureShader] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        auto textureShader = new TextureShader();
        textureShader->loadShader(vertexShaderStr, fragmentShaderStr);

        /// load texture
        textureShader->setAttr(Shader::getTextureFromDDS(uvddsStr));
        textureShader->setUniformLocationAttr("textureSampler");
        textureShader->setUniformLocationMVP("MVP");
        return (void*) textureShader;
    };
};

class YamlHandleColorShader : public YamlHandle {
    std::string id;
    std::string vertexShaderStr;
    std::string fragmentShaderStr;

public:
    YamlHandleColorShader() : YamlHandle(stringCode::colorshader) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::id:
                id = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::vertsh:
                vertexShaderStr = *(std::string*) yamlHandle->getFeature();
                break;
            case stringCode::fragsh:
                fragmentShaderStr = *(std::string*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleColorShader] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        auto colorShader = new ColorShader();
        colorShader->loadShader(vertexShaderStr, fragmentShaderStr);

        colorShader->setUniformLocationMVP("MVP");
        return (void*) colorShader;
    };
};

class YamlHandleGetByID : public YamlHandle {
protected:
    YamlHandleGLGE* objects;
public:
    YamlHandleGetByID(YamlHandleGLGE* objects, stringCode stringCode)
          : YamlHandle(stringCode), objects(objects) {};
};

class YamlHandleGetByIDPhysicsBody : public YamlHandleGetByID {
    PhysicsBody* feature{};

public:
    YamlHandleGetByIDPhysicsBody(YamlHandleGLGE* objects, stringCode stringcode)
          : YamlHandleGetByID(objects, stringcode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            std::string str = value.substr(1, value.size() - 2);

            feature = objects->getPhysicsBodyByID(str);
        } else {
            std::cerr << "[YamlHandleGetByID] please enter a string" << std::endl;
            exit(4);
        }
    };

    void* getFeature() override {
        return (void*) feature;
    };
};

class YamlHandleGetByIDWindow : public YamlHandleGetByID {
    Window* feature{};

public:
    YamlHandleGetByIDWindow(YamlHandleGLGE* objects, stringCode stringcode)
          : YamlHandleGetByID(objects, stringcode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            std::string str = value.substr(1, value.size() - 2);

            feature = objects->getWindowByID(str);
        } else {
            std::cerr << "[YamlHandleGetByID] please enter a string" << std::endl;
            exit(4);
        }
    };

    void* getFeature() override {
        return (void*) feature;
    };
};

class YamlHandleGetByIDMesh : public YamlHandleGetByID {
    Mesh* feature{};

public:
    YamlHandleGetByIDMesh(YamlHandleGLGE* objects, stringCode stringcode)
          : YamlHandleGetByID(objects, stringcode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            std::string str = value.substr(1, value.size() - 2);

            feature = objects->getMeshByID(str);
        } else if (value == "nullptr") {
            feature = nullptr;
        } else {
            std::cerr << "[YamlHandleID] please enter a string" << std::endl;
            exit(4);
        }
    };

    void* getFeature() override {
        return (void*) feature;
    };
};


class YamlHandleGetByIDHeightMap : public YamlHandleGetByID {
    HeightMap* feature{};

public:
    YamlHandleGetByIDHeightMap(YamlHandleGLGE* objects, stringCode stringcode)
          : YamlHandleGetByID(objects, stringcode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            std::string str = value.substr(1, value.size() - 2);

            feature = objects->getHeightMapByID(str);
        } else if (value == "nullptr") {
            feature = nullptr;
        } else {
            std::cerr << "[YamlHandleID] please enter a string" << std::endl;
            exit(4);
        }
    };

    void* getFeature() override {
        return (void*) feature;
    };
};


class YamlHandleGetByIDColorShader : public YamlHandleGetByID {
    ColorShader* feature{};

public:
    YamlHandleGetByIDColorShader(YamlHandleGLGE* objects, stringCode stringcode)
          : YamlHandleGetByID(objects, stringcode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            std::string str = value.substr(1, value.size() - 2);

            feature = objects->getColorShaderByID(str);
        } else if (value == "nullptr") {
            feature = nullptr;
        } else {
            std::cerr << "[YamlHandleID] please enter a string" << std::endl;
            exit(4);
        }
    };

    void* getFeature() override {
        return (void*) feature;
    };
};

class YamlHandleGetByIDTextureShader : public YamlHandleGetByID {
    TextureShader* feature{};

public:
    YamlHandleGetByIDTextureShader(YamlHandleGLGE* objects, stringCode stringcode)
          : YamlHandleGetByID(objects, stringcode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            std::string str = value.substr(1, value.size() - 2);

            feature = objects->getTextureShaderByID(str);
        } else if (value == "nullptr") {
            feature = nullptr;
        } else {
            std::cerr << "[YamlHandleID] please enter a string" << std::endl;
            exit(4);
        }
    };

    void* getFeature() override {
        return (void*) feature;
    };
};


class YamlHandleVec3 : public YamlHandle {
    glm::vec3 feature{};

public:
    explicit YamlHandleVec3(stringCode stringCode) : YamlHandle(stringCode) {};

    void handle(YamlHandle* yamlHandle) override {
        switch (yamlHandle->getType()) {
            case stringCode::x:
                feature.x = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::y:
                feature.y = *(float*) yamlHandle->getFeature();
                break;
            case stringCode::z:
                feature.z = *(float*) yamlHandle->getFeature();
                break;
            default:
                std::cerr << "[YamlHandleVec3] unsupported feature: " << yamlHandle->getType() << std::endl;
                exit(4);
        }
    }

    void* getFeature() override {
        return (void*) &feature;
    };
};

class YamlHandleFloat : public YamlHandle {
    float feature{};
public:
    explicit YamlHandleFloat(stringCode stringCode) : YamlHandle(stringCode) {};

    void handle(std::string value) override {
        char** ptr = nullptr;
        feature = (float) strtod(value.c_str(), ptr);
    };

    void* getFeature() override {
        return (void*) &feature;
    };
};

class YamlHandleString : public YamlHandle {
    std::string feature;
public:
    explicit YamlHandleString(stringCode stringCode) : YamlHandle(stringCode) {};

    void handle(std::string value) override {
        if (value[0] == '\"' && value[value.size() - 1] == '\"') {
            feature = value.substr(1, value.size() - 2);
        } else {
            std::cerr << "[YamlHandleString] please enter a string";
            exit(4);
        }
    }

    void* getFeature() override {
        return (void*) &feature;
    }
};


class YamlHandleInt : public YamlHandle {
    int feature;
public:
    explicit YamlHandleInt(stringCode stringCode) : YamlHandle(stringCode) {};

    void handle(std::string value) override {
        char** ptr = nullptr;
        feature = (int) strtol(value.c_str(), ptr, 10);
    };

    void* getFeature() override {
        return (void*) &feature;
    };
};


class YamlReader {
private:
    YamlHandle* glgeHandle{};

    std::map<std::string, YamlHandle*> keyToFunc;

public:
    YamlReader();

    void readFile(const std::string &string);

    YamlData* getData() {
        return (YamlData*) glgeHandle->getFeature();
    };
};


#endif //GLGEPLUSPLUS_YAMLREADER_H
