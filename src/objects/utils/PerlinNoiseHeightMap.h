//
// Created by thijs on 01-11-20.
//

#ifndef GLGEPLUSPLUS_PERLINNOISEHEIGHTMAP_H
#define GLGEPLUSPLUS_PERLINNOISEHEIGHTMAP_H


#include "HeightMap.h"

class AmpPhaseFreq {
public:
    AmpPhaseFreq(float a, float p, float f) : amplitude(a), phase(p), frequency(f) {};

    float amplitude;
    float phase;
    float frequency;
};

class PerlinNoiseHeightMap : public HeightMap {

private:
    std::vector<AmpPhaseFreq> xAmpPhaseFreqs;
    std::vector<AmpPhaseFreq> zAmpPhaseFreqs;

public:
    PerlinNoiseHeightMap(std::string id_, float length_, float width_, glm::vec3 lowerCorner, float squareSize_) {
        id = std::move(id_);
        length = length_;
        width = width_;
        corner = lowerCorner;
        squareSize = squareSize_;

        xAmpPhaseFreqs = {};
        zAmpPhaseFreqs = {};
        for (int i = 0; i < 10; i++) {
            AmpPhaseFreq xapf((float)i/8.0f, (float)i+2.0f, 2.0f/((float)i+1.0f));
            xAmpPhaseFreqs.emplace_back(xapf);

            AmpPhaseFreq zapf((float)(i*i)/100.0f, (float)i-2.0f, (float)i/40.0f);
            zAmpPhaseFreqs.emplace_back(zapf);
        }
        auto lengthSize = static_cast<int>(length/squareSize);
        auto widthSize = static_cast<int>(width/squareSize);
        height = std::vector<std::vector<float>>(lengthSize, std::vector<float>(widthSize, 0.0f));
        meshData = createHeightMapMeshData();
    }

    float getHeight(glm::vec3 pos) const override;
};


#endif //GLGEPLUSPLUS_PERLINNOISEHEIGHTMAP_H
