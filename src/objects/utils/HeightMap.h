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
    std::vector<std::vector<float>> height;
    glm::vec3 corner;
    float squareSize;

    MeshData* meshData;

public:
    float getXLength() const;
    float getZLength() const;

    bool isPositionAbove(glm::vec3 pos) const;
    virtual float getHeight(glm::vec3 pos) const = 0;
    float getHeightFromMesh(glm::vec3 pos) const;

    MeshData* getMeshData() const;

    MeshData* createHeightMapMeshData(float length, float width, glm::vec3 lowerCorner, float sqSize);
    void updateMesh(HeightMapMesh* heightMapMesh);

    HeightMap(glm::vec3 lowerCorner, float squareSize)
            : corner(lowerCorner), squareSize(squareSize), meshData(nullptr) {
    }
};


#endif //GLGEPLUSPLUS_HEIGHTMAP_H
