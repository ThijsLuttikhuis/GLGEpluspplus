//
// Created by thijs on 19-08-20.
//

#ifndef GLGEPLUSPLUS_CAMERA_H
#define GLGEPLUSPLUS_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "../objects/PhysicsBody.h"
#include "PosAngle.h"

class Camera : public PosAngle {
private:
    PhysicsBody* body;
    float fieldOfView;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 MVP;

public:
    Camera(PhysicsBody* body, float fov)
            : body(body), fieldOfView(fov) {};

    float getFieldOfView() const;
    const glm::mat4 &getViewMatrix() const;
    const glm::mat4 &getProjectionMatrix() const;
    const glm::mat4 &getMVP() const;

    void setFieldOfView(float fieldOfView);

    void updateMatrices(float fov, float near, float far);
    void updatePosition();
};


#endif //GLGEPLUSPLUS_CAMERA_H
