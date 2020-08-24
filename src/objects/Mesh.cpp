//
// Created by thijs on 23-08-20.
//

#include <iostream>
#include "Mesh.h"

Mesh::Mesh(uint vertexLocation_, uint uvLocation_) : vertexLocation(vertexLocation_), uvLocation(uvLocation_) {
    vertices = {{}};
    uvs = {{}};
    normals = {{}};

    vertexBuffer = {};
    uvBuffer = {};
}

void Mesh::setBuffer(const std::vector<glm::vec3> &vertices_, const std::vector<glm::vec2> &uvs_) {
    vertices = vertices_;
    uvs = uvs_;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
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
