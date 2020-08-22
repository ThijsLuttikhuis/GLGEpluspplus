//
// Created by thijs on 19-08-20.
//

#include "Camera.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

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

glm::vec3 Camera::getDirection() const {
    return {std::cos(verticalAngle) * std::sin(horizontalAngle),
                           std::sin(verticalAngle),
                           std::cos(verticalAngle) * std::cos(horizontalAngle)};
}

glm::vec3 Camera::getRight() const {
    return {sin(horizontalAngle - M_PI_2),
            0,
            cos(horizontalAngle - M_PI_2)};
}

glm::vec3 Camera::getUp() const {
    return glm::cross(getRight(), getDirection());
}


const glm::mat4 &Camera::getViewMatrix() const {
    return viewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

const glm::mat4 &Camera::getMVP() const {
    return MVP;
}


void Camera::updateMatrices(float aspectRatio, float near, float far) {
    projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, near, far);

    auto pos = getPosition();
    auto dir = getDirection();
    auto up = getUp();

    // Camera matrix
    viewMatrix       = glm::lookAt(
          pos,           // Camera is here
          pos + dir, // and looks here : at the same position, plus "direction"
          up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 ModelMatrix = glm::mat4(1.0);
    MVP = projectionMatrix * viewMatrix * ModelMatrix;
}


