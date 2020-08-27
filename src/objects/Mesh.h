//
// Created by thijs on 23-08-20.
//

#ifndef GLGEPLUSPLUS_MESH_H
#define GLGEPLUSPLUS_MESH_H


#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class Mesh {
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<uint> indices;

    uint vertexBuffer;
    uint uvBuffer;

    uint vertexLocation;
    uint uvLocation;
public:
    Mesh(uint vertexLocation, uint uvLocation);
    ~Mesh();

#define CubeMesh() Mesh()

    void setBuffer(const std::vector<glm::vec3> &vertices_,
                    const std::vector<glm::vec2> &uvs_);

    const uint &getVertexBuffer() const;
    const uint &getUVBuffer() const;

    void enableAttributeBuffer();

    void disableAttributeBuffer();

    int triangleSize() const;

    void draw();

    static std::vector<glm::vec3>
    CreateCuboid(float length, float width, float height, float xCenter, float yCenter, float zCenter,
                 float horizontalAngle, float verticalAngle);
};


#endif //GLGEPLUSPLUS_MESH_H
