//
// Created by thijs on 30-08-20.
//

#ifndef GLGEPLUSPLUS_OBJECT_H
#define GLGEPLUSPLUS_OBJECT_H


#include "mesh/Mesh.h"
#include "PhysicsBody.h"

class Object {
private:
    Mesh* mesh;
    PhysicsBody* body;
public:

    Object(Mesh* mesh, PhysicsBody* physicsBody);


};


#endif //GLGEPLUSPLUS_OBJECT_H
