//
// Created by thijs on 30-08-20.
//

#ifndef GLGEPLUSPLUS_OBJECT_H
#define GLGEPLUSPLUS_OBJECT_H


#include "../window/mesh/Mesh.h"
#include "PhysicsBody.h"
#include "../window/shader/Shader.h"

class Object {
private:
    Window* handle;

    Mesh* mesh;
    Shader* shader;

public:

    Object(Window* window, Mesh* mesh, Shader* shader, PhysicsBody* physicsBody)
            : handle(window), mesh(mesh), shader(shader) {};

    // non-physical object
    Object(Window* window, Mesh* mesh, Shader* shader)
            : handle(window), mesh(mesh), shader(shader) {};

    void draw();
};


#endif //GLGEPLUSPLUS_OBJECT_H
