//
// Created by thijs on 31-08-20.
//

#include "ColorMesh.h"

void ColorMesh::setBuffer(MeshData* mesh_) {
    mesh = mesh_;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(glm::vec3), &mesh->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &attrBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, attrBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->colorData.size() * mesh->getSize(), &mesh->colorData[0], GL_STATIC_DRAW);
}

void ColorMesh::enableAttributeBuffer() {
    glEnableVertexAttribArray(vertexLocation);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(attrLocation);
    glBindBuffer(GL_ARRAY_BUFFER, attrBuffer);
    glVertexAttribPointer(attrLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ColorMesh::disableAttributeBuffer() {
    glDisableVertexAttribArray(vertexLocation);
    glDisableVertexAttribArray(attrLocation);
}
