//
// Created by thijs on 31-08-20.
//

#ifndef GLGEPLUSPLUS_COLORMESH_H
#define GLGEPLUSPLUS_COLORMESH_H

#include "Mesh.h"



class ColorMeshData : public MeshData {
public:
    ColorMeshData() : MeshData() {};

    std::vector<glm::vec3> normals;

    uint getSize() const override {
        return sizeof(colorData[0])*3;
    }
};

class ColorMesh : public Mesh {
private:

public:
    ColorMesh(uint vertexLocation_, uint attrLocation_) : Mesh(vertexLocation_, attrLocation_) {};

    void setBuffer(MeshData* mesh_) override;
    void enableAttributeBuffer() override;
    void disableAttributeBuffer() override;
};


#endif //GLGEPLUSPLUS_COLORMESH_H
