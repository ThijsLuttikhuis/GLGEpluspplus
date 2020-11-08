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
    float dynamicFriction = 2.0f;
    float staticFrictionThreshold = 2.5f;
public:

    FloorInteraction(std::vector<PhysicsBody*> physicsbody, HeightMap* floor, float height = 0, int priority = 0)
    : Interaction(std::move(physicsbody), priority), floor(floor), heightAboveFloor(height) {};

    void update() override;
};


#endif //GLGEPLUSPLUS_FLOORINTERACTION_H
