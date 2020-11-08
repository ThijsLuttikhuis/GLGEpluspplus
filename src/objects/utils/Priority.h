//
// Created by thijs on 08-11-20.
//

#ifndef GLGEPLUSPLUS_PRIORITY_H
#define GLGEPLUSPLUS_PRIORITY_H


class Priority {
public:
    int priority;
public:
    explicit Priority(int priority) : priority(priority) {};

    bool operator <(const Priority &other) const {
        return priority > other.priority;
    }
};


#endif //GLGEPLUSPLUS_PRIORITY_H
