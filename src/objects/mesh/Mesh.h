//
// Created by thijs on 23-08-20.
//

#ifndef GLGEPLUSPLUS_MESH_H
#define GLGEPLUSPLUS_MESH_H


#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>


class MeshData {
public:
    //TODO: indexed vertices

    MeshData() = default;
    virtual ~MeshData() = default;

    std::vector<glm::vec3> vertices;
    std::vector<float> colorData;
    std::vector<uint> indices;

    virtual uint getSize() const = 0;
};


class Mesh {
protected:
    MeshData* mesh;

    uint vertexBuffer;
    uint attrBuffer;

    uint vertexLocation;
    uint attrLocation;
public:
    Mesh(uint vertexLocation_, uint attrLocation_);
    ~Mesh();

    virtual void setBuffer(MeshData* mesh_) = 0;

    virtual void enableAttributeBuffer() = 0;
    virtual void disableAttributeBuffer() = 0;

    int triangleSize() const;

    void draw();

    static MeshData* CreateCuboid(float length, float width, float height,
                                    float xCenter, float yCenter, float zCenter,
                                    float horizontalAngle, float verticalAngle);

    static MeshData* CreateSphere(float radius,
                                    float xCenter, float yCenter, float zCenter,
                                    float horizontalAngle, float verticalAngle, int n = 100);
};


#endif //GLGEPLUSPLUS_MESH_H
