//
// Created by thijs on 23-08-20.
//

#ifndef GLGEPLUSPLUS_MESH_H
#define GLGEPLUSPLUS_MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "../shader/Shader.h"
#include "../../objects/utils/Priority.h"

class MeshData {
public:
    //TODO: indexed vertices

    MeshData() = default;
    virtual ~MeshData() = default;

    std::vector<glm::vec3> vertices;
    std::vector<float> colorData;
    std::vector<uint> indices;

    //TODO: USE OPENGL TO TRANSLATE MATRIX!!
    void translateMesh(glm::vec3 dPos) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i].x += 1;
        }
        for (auto &&vertex : vertices) {
            vertex += dPos;
        }
    }
    void translateMesh(float dX, float dY, float dZ) {
        translateMesh(glm::vec3(dX, dY, dZ));
    }
    virtual uint getSize() const = 0;
};


class Mesh : public Priority {
protected:
    Window* handle;
    Shader* shader;

    MeshData* mesh;


protected:

    uint vertexBuffer;
    uint attrBuffer;

    uint vertexLocation;
    uint attrLocation;
public:
    Mesh(Window* window, Shader* shader_, uint vertexLocation_, uint attrLocation_);
    virtual ~Mesh();

    virtual void setBuffer(MeshData* mesh_) = 0;

    virtual void enableAttributeBuffer() = 0;
    virtual void disableAttributeBuffer() = 0;

    int triangleSize() const;
    MeshData* getMeshData() const;

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
