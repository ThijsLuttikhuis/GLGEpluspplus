//
// Created by thijs on 31-10-20.
//

#include "FloorInteraction.h"

void FloorInteraction::update() {
    for (auto &body : bodies) {
        auto pos = body->getPosition();
        if (!floor->isPositionAbove(pos)) {
            continue;
        }

        pos.y -= heightAboveFloor;
        float floorHeight = floor->getHeight(pos);
        if (pos.y < floorHeight) {
            auto vel = body->getVelocity();
            if (vel.y < 0.0f) {
                vel.y = 0.0f;
                if (vel.length() < staticFrictionThreshold) {
                    vel.x = 0.0f;
                    vel.z = 0.0f;
                }
                else {
                    auto force = body->getForce();
                    force.x -= vel.x * dynamicFriction;
                    force.z -= vel.z * dynamicFriction;
                    body->setForce(force);
                }
            }

            body->setVelocity(vel);
            pos.y = floorHeight + heightAboveFloor - delta;
            body->setPosition(pos);


        }
    }
}
