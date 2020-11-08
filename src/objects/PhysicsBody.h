//
// Created by thijs on 30-08-20.
//

#ifndef GLGEPLUSPLUS_PHYSICSBODY_H
#define GLGEPLUSPLUS_PHYSICSBODY_H


#include "../window/mesh/Mesh.h"
#include "../window/PosAngle.h"
#include "utils/Priority.h"

class PhysicsBody : public PosAngle, public Priority {
private:
    Mesh* mesh;

    glm::vec3 velocity = glm::vec3(0);
    glm::vec3 force = glm::vec3(0);

public:
    void setVelocity(const glm::vec3 &vel);
    void setForce(const glm::vec3 &force);

    const glm::vec3 &getVelocity() const;
    const glm::vec3 &getForce() const;

    explicit PhysicsBody(Mesh* mesh_) : PosAngle(), Priority(0), mesh(mesh_) {}
    PhysicsBody(Mesh* mesh_, glm::vec3 position, glm::vec3 velocity, float horizontalAngle = 0, float verticalAngle = 0)
                : PosAngle(position, horizontalAngle, verticalAngle), Priority(0), mesh(mesh_), velocity(velocity) {}
    virtual ~PhysicsBody() = default;

    void update(float dt);
};


#endif //GLGEPLUSPLUS_PHYSICSBODY_H
