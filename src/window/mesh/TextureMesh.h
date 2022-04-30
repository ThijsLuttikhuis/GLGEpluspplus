//
// Created by thijs on 31-08-20.
//

#ifndef GLGEPLUSPLUS_TEXTUREMESH_H
#define GLGEPLUSPLUS_TEXTUREMESH_H

#include "Mesh.h"

#include <utility>

class TextureMeshData : public MeshData {
public:
    TextureMeshData() : MeshData() {};

    std::vector<glm::vec3> normals;

    uint getSize() const override {
        return sizeof(colorData[0]) * 2;
    }
};

class TextureMesh : public Mesh {
private:


public:
    TextureMesh(std::string id, Window* window, Shader* shader_,
                uint vertexLocation_, uint attrLocation_, int priority = 0)
          : Mesh(std::move(id), window, shader_, vertexLocation_, attrLocation_, priority) {};

    void setBuffer(MeshData* mesh_) override;

    void enableAttributeBuffer() override;

    void disableAttributeBuffer() override;
};


#endif //GLGEPLUSPLUS_TEXTUREMESH_H
