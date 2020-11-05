//
// Created by thijs on 01-11-20.
//

#include <cmath>
#include <cfloat>
#include "PerlinNoiseHeightMap.h"


float PerlinNoiseHeightMap::getHeight(glm::vec3 pos) const {

    float h = 0.0f;

    for (auto &apf : xAmpPhaseFreqs) {
        h += apf.amplitude * std::sin(apf.frequency * pos.x + apf.phase);
    }
    for (auto &apf : zAmpPhaseFreqs) {
        h += apf.amplitude * std::sin(apf.frequency * pos.z + apf.phase);
    }
    return h;


//
//    auto h = 1.0 * std::sin(pos.x) + 0.4 * std::cos(pos.z);
//    h += 1.0 * std::sin(0.4 * pos.x) + 0.6 * std::cos(0.6 * pos.z);
//    h += 1.0 * std::sin(0.012 * pos.x) + 2.0 * std::cos(0.05 * pos.z);


}