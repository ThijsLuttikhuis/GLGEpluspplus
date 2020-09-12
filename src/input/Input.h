//
// Created by thijs on 12-09-20.
//

#ifndef GLGEPLUSPLUS_INPUT_H
#define GLGEPLUSPLUS_INPUT_H


#include "../window/Window.h"

class Input {
protected:
    Window* handle;

public:
    explicit Input(Window* window) : handle(window) {};
    virtual ~Input() = default;
    virtual void update() = 0;
};


#endif //GLGEPLUSPLUS_INPUT_H
