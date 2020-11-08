//
// Created by thijs on 29-09-20.
//

#ifndef GLGEPLUSPLUS_CONSTANTFORCE_H
#define GLGEPLUSPLUS_CONSTANTFORCE_H


#include <utility>
#include <glm/vec3.hpp>
#include "../PhysicsBody.h"
#include "Interaction.h"

class ConstantForce : public Interaction {
private:
    glm::vec3 forceStrength;

public:
    ConstantForce(std::vector<PhysicsBody*> physicsbody, glm::vec3 forceStrength, int priority = 0)
          : Interaction(std::move(physicsbody), priority), forceStrength(forceStrength) {};

    void update() override;

};


#endif //GLGEPLUSPLUS_CONSTANTFORCE_H
