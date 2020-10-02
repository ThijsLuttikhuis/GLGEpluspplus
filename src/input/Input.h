//
// Created by thijs on 12-09-20.
//

#ifndef GLGEPLUSPLUS_INPUT_H
#define GLGEPLUSPLUS_INPUT_H


#include <utility>

#include "../window/Window.h"
#include "../objects/Interactions/Interaction.h"

class Input : public Interaction {
protected:
    Window* handle;

public:
    explicit Input(Window* window, std::vector<PhysicsBody*> bodies) : Interaction(std::move(bodies)), handle(window) {};
};


#endif //GLGEPLUSPLUS_INPUT_H
