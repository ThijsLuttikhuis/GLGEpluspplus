//
// Created by thijs on 30-08-20.
//

#ifndef GLGEPLUSPLUS_PHYSICSBODY_H
#define GLGEPLUSPLUS_PHYSICSBODY_H


#include "../window/mesh/Mesh.h"

class PhysicsBody {
private:
    Mesh* mesh;

    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 force;

public:
    void setVel(const glm::vec3 &vel);
    void setPos(const glm::vec3 &pos);
    void setForce(const glm::vec3 &force);

    const glm::vec3 &getPos() const;
    const glm::vec3 &getVel() const;
    const glm::vec3 &getForce() const;

    explicit PhysicsBody(Mesh* mesh_) : mesh(mesh_), pos(0), vel(0) {}
    PhysicsBody(Mesh* mesh_, glm::vec3 pos, glm::vec3 vel) : mesh(mesh_), pos(pos), vel(vel) {}

    void update(float dt);
};


#endif //GLGEPLUSPLUS_PHYSICSBODY_H
