//
// Created by thijs on 29-09-20.
//

#include "Interaction.h"

void Interaction::addBody(PhysicsBody* body) {
    bodies.push_back(body);
}

void Interaction::setBodies(std::vector<PhysicsBody*> bodies_) {
    bodies = bodies_;
}
