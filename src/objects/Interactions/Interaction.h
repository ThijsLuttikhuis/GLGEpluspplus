//
// Created by thijs on 29-09-20.
//

#ifndef GLGEPLUSPLUS_INTERACTION_H
#define GLGEPLUSPLUS_INTERACTION_H


#include <utility>
#include <vector>
#include "../PhysicsBody.h"

class Interaction {
protected:
    std::vector<PhysicsBody*> bodies;

public:
    explicit Interaction(std::vector<PhysicsBody*> bodies_)
        : bodies(std::move(bodies_)) {};

    virtual ~Interaction() = default;

    virtual void update() = 0;
};


#endif //GLGEPLUSPLUS_INTERACTION_H
