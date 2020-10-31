//
// Created by thijs on 31-10-20.
//

#ifndef GLGEPLUSPLUS_HEIGHTMAP_H
#define GLGEPLUSPLUS_HEIGHTMAP_H


#include <vector>
#include <glm/vec3.hpp>
#include "../../window/mesh/HeightMapMesh.h"

class HeightMap {
private:
    std::vector<std::vector<float>> height;
    glm::vec3 corner;
    float squareSize;

    MeshData* meshData;

public:
    float getHeight(glm::vec3 pos) const;
    MeshData* getMeshData() const;

    MeshData* createHeightMapMeshData(float length, float width, glm::vec3 lowerCorner, float sqSize);
    void updateMesh(HeightMapMesh* heightMapMesh);

    HeightMap(float length, float width, glm::vec3 lowerCorner, float squareSize)
            : corner(lowerCorner), squareSize(squareSize) {

        auto lengthSize = static_cast<int>(length/squareSize);
        auto widthSize = static_cast<int>(width/squareSize);
        height = std::vector<std::vector<float>>(lengthSize, std::vector<float>(widthSize, 0.0f));
        meshData = createHeightMapMeshData(length, width, lowerCorner, squareSize);
    }
};


#endif //GLGEPLUSPLUS_HEIGHTMAP_H
