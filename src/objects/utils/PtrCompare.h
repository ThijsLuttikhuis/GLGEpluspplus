//
// Created by thijs on 08-11-20.
//

#ifndef GLGEPLUSPLUS_PTRCOMPARE_H
#define GLGEPLUSPLUS_PTRCOMPARE_H

template<class T> struct PtrCompare {
    bool operator()(T* lhs, T* rhs) const {
        return *lhs < *rhs;
    }
};

#endif //GLGEPLUSPLUS_PTRCOMPARE_H
