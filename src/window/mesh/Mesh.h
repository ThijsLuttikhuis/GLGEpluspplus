//
// Created by thijs on 23-08-20.
//

#ifndef GLGEPLUSPLUS_MESH_H
#define GLGEPLUSPLUS_MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "../shader/Shader.h"

class MeshData {
public:
    //TODO: indexed vertices

    MeshData() = default;
    virtual ~MeshData() = default;

    std::vector<glm::vec3> vertices;
    std::vector<float> colorData;
    std::vector<uint> indices;

    void translateMesh(float dX, float dY, float dZ) {
        for (auto &vertex : vertices) {
            vertex.x += dX;
            vertex.y += dY;
            vertex.z += dZ;
        }
    }
    virtual uint getSize() const = 0;
};


class Mesh {
private:
    Window* handle;
    Shader* shader;

protected:
    MeshData* mesh;

    uint vertexBuffer;
    uint attrBuffer;

    uint vertexLocation;
    uint attrLocation;
public:
    Mesh(Window* window, Shader* shader_, uint vertexLocation_, uint attrLocation_);
    ~Mesh();

    virtual void setBuffer(MeshData* mesh_) = 0;

    virtual void enableAttributeBuffer() = 0;
    virtual void disableAttributeBuffer() = 0;

    int triangleSize() const;

    void draw();

    static MeshData* CreateCuboid(float length, float height, float width,
                                    float xCenter, float yCenter, float zCenter,
                                    float horizontalAngle, float verticalAngle);

    static MeshData* CreateSphere(float radius,
                                    float xCenter, float yCenter, float zCenter,
                                    float horizontalAngle, float verticalAngle, int n = 100);

    static MeshData* CreatePlane(float length, float width,
                                    float xCenter, float yCenter, float zCenter, float squareSize = 0.5f);
};


#endif //GLGEPLUSPLUS_MESH_H
