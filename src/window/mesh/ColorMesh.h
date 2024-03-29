//
// Created by thijs on 31-08-20.
//

#ifndef GLGEPLUSPLUS_COLORMESH_H
#define GLGEPLUSPLUS_COLORMESH_H

#include "Mesh.h"
#include "../shader/Shader.h"


class ColorMeshData : public MeshData {
public:
    ColorMeshData() : MeshData() {};

    std::vector<glm::vec3> normals;

    uint getSize() const override {
        return sizeof(colorData[0])*3;
    }
};

class ColorMesh : public Mesh {

public:
    ColorMesh(std::string id, Window* window, Shader* shader_, uint vertexLocation_, uint attrLocation_, int priority = 0)
        : Mesh(std::move(id), window, shader_, vertexLocation_, attrLocation_, priority) {};

    void setBuffer(MeshData* mesh_) override;
    void enableAttributeBuffer() override;
    void disableAttributeBuffer() override;
};


#endif //GLGEPLUSPLUS_COLORMESH_H
