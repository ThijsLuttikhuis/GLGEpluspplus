//
// Created by thijs on 31-10-20.
//

#ifndef GLGEPLUSPLUS_FLOORINTERACTION_H
#define GLGEPLUSPLUS_FLOORINTERACTION_H


#include "Interaction.h"
#include "../utils/HeightMap.h"

class FloorInteraction : public Interaction {
private:
    HeightMap* floor;
    float heightAboveFloor;
    float delta = 0.2;
public:

    FloorInteraction(std::vector<PhysicsBody*> physicsbody, HeightMap* floor, float height = 0)
    : Interaction(std::move(physicsbody)), floor(floor), heightAboveFloor(height) {};

    void update() override;
};


#endif //GLGEPLUSPLUS_FLOORINTERACTION_H
