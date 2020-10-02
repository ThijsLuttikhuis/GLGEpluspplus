//
// Created by thijs on 30-08-20.
//

#include "PhysicsBody.h"

void PhysicsBody::update(float dt) {
    vel = vel + force * dt;
    pos = pos + vel * dt;
    force = glm::vec3{0};
}

const glm::vec3 &PhysicsBody::getPos() const {
    return pos;
}

const glm::vec3 &PhysicsBody::getVel() const {
    return vel;
}

void PhysicsBody::setPos(const glm::vec3 &pos_) {
    pos = pos_;
}

void PhysicsBody::setVel(const glm::vec3 &vel_) {
    vel = vel_;
}

void PhysicsBody::setForce(const glm::vec3 &force_) {
    force = force_;
}

const glm::vec3 &PhysicsBody::getForce() const {
    return force;
}
