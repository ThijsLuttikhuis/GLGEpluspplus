//
// Created by thijs on 05-11-20.
//

#include <cmath>
#include <glm/glm.hpp>
#include "PosAngle.h"

const glm::vec3 &PosAngle::getPosition() const {
    return position;
}

float PosAngle::getHorizontalAngle() const {
    return horizontalAngle;
}

float PosAngle::getVerticalAngle() const {
    return verticalAngle;
}

void PosAngle::setPosition(const glm::vec3 &position_) {
    position = position_;
}

void PosAngle::setHorizontalAngle(float horizontalAngle_) {
    horizontalAngle = horizontalAngle_;
}

void PosAngle::setVerticalAngle(float verticalAngle_) {
    verticalAngle = verticalAngle_;
}

glm::vec3 PosAngle::getDirection() const {
    return {std::cos(verticalAngle) * std::sin(horizontalAngle),
            std::sin(verticalAngle),
            std::cos(verticalAngle) * std::cos(horizontalAngle)};
}

glm::vec3 PosAngle::getRight() const {
    return {sin(horizontalAngle - M_PI_2),
            0,
            cos(horizontalAngle - M_PI_2)};
}

glm::vec3 PosAngle::getUp() const {
    return glm::cross(getRight(), getDirection());
}

glm::vec3 PosAngle::getHorizonForwards() const {
    auto dir = getDirection();
    auto length = glm::length(dir);
    glm::vec3 forwards = glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))*length;
    return forwards;
}
