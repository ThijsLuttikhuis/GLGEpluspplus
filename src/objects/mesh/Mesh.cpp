//
// Created by thijs on 23-08-20.
//

#include <iostream>
#include <glm/vec4.hpp>
#include <cmath>
#include "Mesh.h"
#include "TextureMesh.h"
#include "ColorMesh.h"
#include <random>


Mesh::Mesh(uint vertexLocation_, uint attrLocation_) : vertexLocation(vertexLocation_), attrLocation(attrLocation_) {
    mesh = nullptr;

    vertexBuffer = {};
    attrBuffer = {};
}

Mesh::~Mesh() {
    delete mesh;

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &attrBuffer);
}


int Mesh::triangleSize() const {
    return mesh->vertices.size();
}

void Mesh::draw() {
    // draw triangles
    enableAttributeBuffer();
    glDrawArrays(GL_TRIANGLES, 0, triangleSize());
    disableAttributeBuffer();
}

MeshData* Mesh::CreateCuboid(float length, float width, float height,
                                          float xCenter, float yCenter, float zCenter,
                                          float horizontalAngle, float verticalAngle) {
    MeshData* mesh = new TextureMeshData();

    // make eight vertices
    std::vector<glm::vec3> vertices = {};
    for (int i = 0; i < 8; i++) {
        float x1 = -length/2.0f + xCenter;
        float x2 = length/2.0f + xCenter;
        float z1 = -width/2.0f + yCenter;
        float z2 = width/2.0f + yCenter;
        float y1 = -height/2.0f + zCenter;
        float y2 = height/2.0f + zCenter;

        glm::vec3 v = {i & (1 << 0) ? x1 : x2,
                       i & (1 << 1) ? y1 : y2,
                       i & (1 << 2) ? z1 : z2};
        std::cout << v.x << v.y << v.z << std::endl;
        vertices.push_back(v);
    }

    // create cuboid from the eight vertices
    std::vector<glm::vec3> cuboidVertices = {
          // from 000:
          // xz faces
          vertices[0], vertices[1], vertices[3],
          vertices[0], vertices[3], vertices[2],
          // zy faces
          vertices[0], vertices[2], vertices[6],
          vertices[0], vertices[6], vertices[4],
          // yx faces
          vertices[0], vertices[4], vertices[5],
          vertices[0], vertices[5], vertices[1],

          // from 111:
          // xy faces
          vertices[7], vertices[5], vertices[4],
          vertices[7], vertices[4], vertices[6],
          // yz faces
          vertices[7], vertices[3], vertices[1],
          vertices[7], vertices[1], vertices[5],
          // zx faces
          vertices[7], vertices[6], vertices[2],
          vertices[7], vertices[2], vertices[3],
    };

    mesh->vertices = cuboidVertices;
    std::vector<float> cuboidUVs = {
          0, 0, 0, 0.333, 0.333, 0.333,
          0, 0, 0.333, 0.333, 0.333, 0,
          0, 0, 0, 0.333, 0.333, 0.333,
          0, 0, 0.333, 0.333, 0.333, 0,
          0, 0, 0, 0.333, 0.333, 0.333,
          0, 0, 0.333, 0.333, 0.333, 0,
          0, 0, 0, 0.333, 0.333, 0.333,
          0, 0, 0.333, 0.333, 0.333, 0,
          0, 0, 0, 0.333, 0.333, 0.333,
          0, 0, 0.333, 0.333, 0.333, 0,
          0, 0, 0, 0.333, 0.333, 0.333,
          0, 0, 0.333, 0.333, 0.333, 0
    };
    mesh->colorData = cuboidUVs;

    return mesh;
}

MeshData* Mesh::CreateSphere(float radius, float xCenter, float yCenter, float zCenter, float horizontalAngle,
                           float verticalAngle, int n) {

    MeshData* mesh = new ColorMeshData();

    int phiVertices = std::sqrt(n);
    float phi = horizontalAngle;
    float phiInc = M_PI * 2.0f / phiVertices;

    int thetaVertices = n / phiVertices;
    float theta = verticalAngle;
    float thetaInc = M_PI / thetaVertices;

    std::vector<glm::vec3> vertices = {{}};
    for (int i = 0; i < thetaVertices + 1; i++) {
        for (int j = 0; j < phiVertices + 1; j++) {

            glm::vec3 vertex = {xCenter + radius * std::sin(theta) * std::cos(phi),
                                yCenter + radius * std::cos(theta),
                                zCenter + radius * std::sin(theta) * std::sin(phi)};

            vertices.push_back(vertex);
            std::cout << phi << std::endl;
            phi += phiInc;
        }
        theta += thetaInc;
    }

    //random numbers
    std::mt19937 generator(1);
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    for (uint i = 0; i < (uint)vertices.size() - phiVertices - 1; i++) {
        uint j = i + 1;
        uint k = i + phiVertices;
        uint l = i + phiVertices - 1;

        std::vector<glm::vec3> triangle = {vertices[i], vertices[j], vertices[k],
                                           vertices[i], vertices[k], vertices[l]};
        mesh->vertices.insert(mesh->vertices.end(), triangle.begin(), triangle.end());

        for (uint r = 0; r < 18; r++) {
            float randomNumber = distribution(generator);
            mesh->colorData.push_back(randomNumber);
        }
    }


    for (uint i = 0; i < (uint) vertices.size(); i++) {

    }

    return mesh;

}
