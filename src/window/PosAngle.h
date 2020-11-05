//
// Created by thijs on 05-11-20.
//

#ifndef GLGEPLUSPLUS_POSANGLE_H
#define GLGEPLUSPLUS_POSANGLE_H


#include <glm/vec3.hpp>

class PosAngle {
protected:
    glm::vec3 position = glm::vec3(0);
    float horizontalAngle = 0;
    float verticalAngle = 0;

public:
    PosAngle() = default;
    PosAngle(glm::vec3 &position, float horizontalAngle, float verticalAngle)
            : position(position), horizontalAngle(horizontalAngle), verticalAngle(verticalAngle) {};

    const glm::vec3 &getPosition() const;
    float getHorizontalAngle() const;
    float getVerticalAngle() const;

    void setPosition(const glm::vec3 &position);
    void setHorizontalAngle(float horizontalAngle);
    void setVerticalAngle(float verticalAngle);

    glm::vec3 getDirection() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;
    glm::vec3 getHorizonForwards() const;
};


#endif //GLGEPLUSPLUS_POSANGLE_H
