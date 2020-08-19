//
// Created by thijs on 19-08-20.
//

#include "Camera.h"

const glm::vec3 &Camera::getPosition() const {
    return position;
}

float Camera::getHorizontalAngle() const {
    return horizontalAngle;
}

float Camera::getVerticalAngle() const {
    return verticalAngle;
}

float Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::setPosition(const glm::vec3 &position_) {
    Camera::position = position_;
}

void Camera::setHorizontalAngle(float horizontalAngle_) {
    Camera::horizontalAngle = horizontalAngle_;
}

void Camera::setVerticalAngle(float verticalAngle_) {
    Camera::verticalAngle = verticalAngle_;
}

void Camera::setFieldOfView(float fieldOfView_) {
    Camera::fieldOfView = fieldOfView_;
}
