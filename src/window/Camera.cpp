//
// Created by thijs on 19-08-20.
//

#include "Camera.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>



float Camera::getFieldOfView() const {
    return fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView_) {
    Camera::fieldOfView = fieldOfView_;
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

void Camera::updatePosition() {
    setPosition(body->getPosition());
    setHorizontalAngle(body->getHorizontalAngle());
    setVerticalAngle(body->getVerticalAngle());
}

