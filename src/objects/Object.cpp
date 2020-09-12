//
// Created by thijs on 30-08-20.
//

#include "Object.h"

void Object::draw() {
    shader->useShader();
    shader->update(handle);
    mesh->draw();
}
