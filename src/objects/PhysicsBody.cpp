//
// Created by thijs on 30-08-20.
//

#include "PhysicsBody.h"

void PhysicsBody::update(float dt) {
    velocity = velocity + force * dt;
    position = position + velocity * dt;
    force = glm::vec3{0};

    if (mesh) {
        glm::vec3 dPos =  velocity * dt;
        mesh->getMeshData()->translateMesh(dPos);
    }
}

const glm::vec3 &PhysicsBody::getVelocity() const {
    return velocity;
}

void PhysicsBody::setVelocity(const glm::vec3 &velocity_) {
    velocity = velocity_;
}

void PhysicsBody::setForce(const glm::vec3 &force_) {
    force = force_;
}

const glm::vec3 &PhysicsBody::getForce() const {
    return force;
}
