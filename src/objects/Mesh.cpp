//
// Created by thijs on 23-08-20.
//

#include "Mesh.h"

Mesh::Mesh() {
    vertices = {{}};
    uvs = {{}};
    normals = {{}};
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
