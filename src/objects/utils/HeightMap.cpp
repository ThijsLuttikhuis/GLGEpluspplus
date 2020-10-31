//
// Created by thijs on 31-10-20.
//

#include <cmath>
#include <cfloat>
#include "HeightMap.h"
#include "../../window/mesh/HeightMapMesh.h"

void HeightMap::updateMesh(HeightMapMesh* heightMapMesh) {

}

MeshData* HeightMap::createHeightMapMeshData(float length, float width, glm::vec3 lowerCorner, float sqSize) {

    MeshData* mesh = new ColorMeshData();

    auto xVertices = static_cast<int>(length / sqSize);
    auto zVertices = static_cast<int>(width / sqSize);
    float xStart = lowerCorner.x;
    float zStart = lowerCorner.z;

    std::vector<glm::vec3> vertices = {{}};
    for (int i = 0; i < xVertices; i++) {
        for (int j = 0; j < zVertices; j++) {

            glm::vec3 vertex = {xStart + (float) i * sqSize,
                                lowerCorner.y,
                                zStart + (float) j * sqSize};

            auto h = 1.0 * std::sin(vertex.x) + 0.4 * std::cos(vertex.z);
            h += 1.0 * std::sin(0.4*vertex.x) + 0.6 * std::cos(0.6*vertex.z);
            h += 1.0 * std::sin(0.012*vertex.x) + 2.0 * std::cos(0.05*vertex.z);
            vertex.y = h;
            height[i][j] = h;

            vertices.push_back(vertex);
            if (i > 0 && j > 1) {
                // create triangles
                auto indexL = [zVertices, i, j](int iRel, int jRel) {
                    return (i + iRel) * zVertices + (j + jRel);
                };
                int iRel[6] = {-1, -1, 0, -1, 0, 0};
                int jRel[6] = {-1, 0, 0, -1, 0, -1};

                for (uint r = 0; r < 6; r++) {
                    mesh->vertices.push_back(vertices[indexL(iRel[r], jRel[r])]);
                }

                // create color
                static float color = 0.0f;
                for (uint r = 0; r < 18; r++) {
                    mesh->colorData.push_back(color);
                }
                color += 1.0f / (float) (xVertices * zVertices);
            }
        }
    }

    return mesh;
}

MeshData* HeightMap::getMeshData() const {
    return meshData;
}

float HeightMap::getHeight(glm::vec3 pos) const {
    float floorDx = (height.size()-1.0f) * squareSize;
    float floorDz = (height[0].size()-1.0f) * squareSize;

    float dx = pos.x - corner.x;
    float dz = pos.z - corner.z;

    if (dx > 0 && dz > 0 && dx < floorDx && dz < floorDz) {
        int xIndex = std::floor(dx / squareSize);
        int zIndex = std::floor(dz / squareSize);

        float xy00 = height[xIndex][zIndex];
        float xy01 = height[xIndex][zIndex+1];
        float xy10 = height[xIndex+1][zIndex];

        float a = std::fmod(dx, squareSize);
        float b = std::fmod(dz, squareSize);
        float h = 0.5f*( xy10 * a + xy00 * (1.0f-a) + xy01 * b + xy00 * (1.0f-b) );

        return h;
    }
    else {
        return - FLT_MAX;
    }
}
