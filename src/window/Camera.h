//
// Created by thijs on 19-08-20.
//

#ifndef GLGEPLUSPLUS_CAMERA_H
#define GLGEPLUSPLUS_CAMERA_H

#include <glm/vec3.hpp>

class Camera {
private:
// Initial position : on +Z
    glm::vec3 position = glm::vec3( 0, 0, 5 );
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float fieldOfView = 45.0f;

public:
    Camera(glm::vec3 pos, float hAngle, float vAngle, float fov)
            : position(pos), horizontalAngle(hAngle), verticalAngle(vAngle), fieldOfView(fov) {};

    Camera() = default;

    const glm::vec3 &getPosition() const;
    float getHorizontalAngle() const;
    float getVerticalAngle() const;
    float getFieldOfView() const;

    void setPosition(const glm::vec3 &position);
    void setHorizontalAngle(float horizontalAngle);
    void setVerticalAngle(float verticalAngle);
    void setFieldOfView(float fieldOfView);

};


#endif //GLGEPLUSPLUS_CAMERA_H
