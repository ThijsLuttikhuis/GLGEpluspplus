//
// Created by thijs on 31-10-20.
//

#include "FloorInteraction.h"

void FloorInteraction::update() {
    for (auto &body : bodies) {
        auto pos = body->getPos();
        pos.y -= heightAboveFloor;
        float floorHeight = floor->getHeight(pos);
        if (pos.y < floorHeight) {
            pos.y = floorHeight + heightAboveFloor;
            body->setPos(pos);

            auto vel = body->getVel();
            vel.y = 0;
            body->setVel(vel);
        }
    }
}
