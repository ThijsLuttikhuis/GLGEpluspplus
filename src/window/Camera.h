//
// Created by thijs on 19-08-20.
//

#ifndef GLGEPLUSPLUS_CAMERA_H
#define GLGEPLUSPLUS_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

class Camera {
private:
// Initial position : on +Z
    glm::vec3 position = glm::vec3( 0, 0, 5 );
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float fieldOfView = 45.0f;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::mat4 MVP;


public:
    Camera(glm::vec3 pos, float hAngle, float vAngle, float fov)
            : position(pos), horizontalAngle(hAngle), verticalAngle(vAngle), fieldOfView(fov) {};

    Camera() = default;

    const glm::vec3 &getPosition() const;
    float getHorizontalAngle() const;
    float getVerticalAngle() const;
    float getFieldOfView() const;

    const glm::mat4 &getViewMatrix() const;
    const glm::mat4 &getProjectionMatrix() const;
    const glm::mat4 &getMVP() const;

    glm::vec3 getDirection() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    void setPosition(const glm::vec3 &position);
    void setHorizontalAngle(float horizontalAngle);
    void setVerticalAngle(float verticalAngle);
    void setFieldOfView(float fieldOfView);

    void updateMatrices(float fov, float near, float far);
};


#endif //GLGEPLUSPLUS_CAMERA_H
