//
// Created by thijs on 29-09-20.
//

#include "ConstantForce.h"

void ConstantForce::update() {
    for (auto &body : bodies) {
        auto force = body->getForce();
        force += forceStrength;
        body->setForce(force);
    }
}
