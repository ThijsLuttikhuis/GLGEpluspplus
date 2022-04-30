//
// Created by thijs on 31-10-20.
//

#ifndef GLGEPLUSPLUS_HEIGHTMAP_H
#define GLGEPLUSPLUS_HEIGHTMAP_H


#include <vector>
#include <glm/vec3.hpp>
#include "../../window/mesh/HeightMapMesh.h"

class HeightMap {
protected:
    std::string id;
    std::vector<std::vector<float>> height{};
    glm::vec3 corner{};
    float squareSize = 0;

    float length = 0;
    float width = 0;

    MeshData* meshData = nullptr;

public:
    HeightMap() = default;

    HeightMap(std::string id, float length, float width, glm::vec3 lowerCorner, float squareSize)
          : id(std::move(id)), corner(lowerCorner), squareSize(squareSize), length(length), width(width), meshData(nullptr) {

        auto lengthSize = static_cast<int>(length/squareSize);
        auto widthSize = static_cast<int>(width/squareSize);
        height = std::vector<std::vector<float>>(lengthSize, std::vector<float>(widthSize, 0.0f));
        meshData = createHeightMapMeshData();
    }

    const std::string &getID() const {
        return id;
    }

    float getXLength() const;

    float getZLength() const;

    bool isPositionAbove(glm::vec3 pos) const;

    virtual float getHeight(glm::vec3 pos) const;

    float getHeightFromMesh(glm::vec3 pos) const;

    MeshData* getMeshData() const;

    MeshData* createHeightMapMeshData();

    void updateMesh(HeightMapMesh* heightMapMesh);
};


#endif //GLGEPLUSPLUS_HEIGHTMAP_H
