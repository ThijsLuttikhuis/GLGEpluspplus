//
// Created by thijs on 29-09-20.
//

#ifndef GLGEPLUSPLUS_INTERACTION_H
#define GLGEPLUSPLUS_INTERACTION_H


#include <utility>
#include <vector>
#include "../PhysicsBody.h"
#include "../utils/Priority.h"


class Interaction : public Priority {

protected:
    std::vector<PhysicsBody*> bodies;

public:
    Interaction(std::vector<PhysicsBody*> bodies, int priority)
        : Priority(priority), bodies(std::move(bodies)) {};
    virtual ~Interaction() = default;

    void addBody(PhysicsBody* body);
    void setBodies(std::vector<PhysicsBody*> bodies);

    virtual void update() = 0;
};


#endif //GLGEPLUSPLUS_INTERACTION_H
