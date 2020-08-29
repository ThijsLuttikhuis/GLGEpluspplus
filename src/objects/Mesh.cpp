//
// Created by thijs on 23-08-20.
//

#include <iostream>
#include <glm/vec4.hpp>
#include "Mesh.h"

Mesh::Mesh(uint vertexLocation_, uint uvLocation_) : vertexLocation(vertexLocation_), uvLocation(uvLocation_) {
    textureMesh = {};

    vertexBuffer = {};
    uvBuffer = {};
}

void Mesh::setBuffer(const std::vector<glm::vec3> &vertices_, const std::vector<glm::vec2> &uvs_) {
    TextureMesh textureMesh_;
    textureMesh_.vertices = vertices_;
    textureMesh_.uvs = uvs_;
    setBuffer(textureMesh_);
}

void Mesh::setBuffer(const TextureMesh &textureMesh_) {
    textureMesh = textureMesh_;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, textureMesh.vertices.size() * sizeof(glm::vec3), &textureMesh.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, textureMesh.uvs.size() * sizeof(glm::vec2), &textureMesh.uvs[0], GL_STATIC_DRAW);
}

const uint &Mesh::getVertexBuffer() const {
    return vertexBuffer;
}

const uint &Mesh::getUVBuffer() const {
    return uvBuffer;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
}

void Mesh::enableAttributeBuffer() {
    glEnableVertexAttribArray(vertexLocation);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(uvLocation);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::disableAttributeBuffer() {
    glDisableVertexAttribArray(vertexLocation);
    glDisableVertexAttribArray(uvLocation);
}

int Mesh::triangleSize() const {
    return textureMesh.vertices.size();
}

void Mesh::draw() {
    // draw triangles
    enableAttributeBuffer();
    glDrawArrays(GL_TRIANGLES, 0, triangleSize());
    disableAttributeBuffer();
}

TextureMesh Mesh::CreateCuboid(float length, float width, float height,
                                          float xCenter, float yCenter, float zCenter,
                                          float horizontalAngle, float verticalAngle) {
    TextureMesh textureMesh;

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
          // xy faces
          vertices[0], vertices[1], vertices[3],
          vertices[0], vertices[3], vertices[2],
          // yz faces
          vertices[0], vertices[2], vertices[6],
          vertices[0], vertices[6], vertices[4],
          // zx faces
          vertices[0], vertices[5], vertices[1],
          vertices[0], vertices[4], vertices[5],

          // from 111:
          // xy faces
          vertices[7], vertices[5], vertices[4],
          vertices[7], vertices[4], vertices[6],
          // yz faces
          vertices[7], vertices[3], vertices[1],
          vertices[7], vertices[1], vertices[5],
          // zx faces
          vertices[7], vertices[2], vertices[3],
          vertices[7], vertices[6], vertices[2],
    };
    textureMesh.vertices = cuboidVertices;

    glm::vec4 faces = {};
    for (int i = 0; i < 6; i++) {

    }

    std::vector<glm::vec2> cuboidUVs = {
          {0, 0},  {},
          {},
          {},

    };


    textureMesh.uvs = cuboidUVs;

    return textureMesh;
    // first:   0  .3  .6   1
    // sec:   0 _____________
    //          |\  |\  |\  |
    //          | \ | \ | \ |
    //          |  \|  \|  \|
    //       .3 _____________
    //          |\  |\  |\  |
    //          | \ | \ | \ |
    //          |  \|  \|  \|
    //       .6 _____________
    //          |\  |\  |\  |
    //          | \ | \ | \ |
    //          |  \|  \|  \|
    //        1 _____________

}
