//
// Created by thijs on 31-10-20.
//

#ifndef GLGEPLUSPLUS_HEIGHTMAPBODY_H
#define GLGEPLUSPLUS_HEIGHTMAPBODY_H


#include <vector>
#include <glm/vec3.hpp>
#include "../window/mesh/HeightMapMesh.h"
#include "utils/HeightMap.h"

class HeightMapBody {
private:
    HeightMapMesh* mesh;
    HeightMap* heightMap;

    double resolution;

};


#endif //GLGEPLUSPLUS_HEIGHTMAPBODY_H
