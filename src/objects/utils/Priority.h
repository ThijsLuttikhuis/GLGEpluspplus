#include <utility>

//
// Created by thijs on 08-11-20.
//

#ifndef GLGEPLUSPLUS_PRIORITY_H
#define GLGEPLUSPLUS_PRIORITY_H


class Priority {
    std::string id;
    int priority;

public:

    Priority(std::string id, int priority) : id(std::move(id)), priority(priority) {};

    const std::string &getID() const {
        return id;
    }

    int getPriority() const {
        return priority;
    }

    bool operator <(const Priority &other) const {
        return priority > other.priority;
    }
};


#endif //GLGEPLUSPLUS_PRIORITY_H
