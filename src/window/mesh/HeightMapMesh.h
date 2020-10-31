//
// Created by thijs on 03-10-20.
//

#ifndef GLGEPLUSPLUS_HEIGHTMAPMESH_H
#define GLGEPLUSPLUS_HEIGHTMAPMESH_H


#include "ColorMesh.h"

class HeightMapMesh : public ColorMesh {
private:

public:
    HeightMapMesh(Window* window, Shader* shader_, uint vertexLocation_, uint attrLocation_)
    : ColorMesh(window, shader_, vertexLocation_, attrLocation_) {};

};


#endif //GLGEPLUSPLUS_HEIGHTMAPMESH_H
