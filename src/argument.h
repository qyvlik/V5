#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "v5.h"

namespace V5 {

#define ARGUMENT_TYPE_LIST(T, K)                  \
    T(Invalid, "Invalid")                         \
    T(Bool, "Bool")                               \
    T(Int, "Int")                                 \
    T(Long, "Long")                               \
    T(Double, "Double")                           \
    T(Char, "Char")                               \
    T(Array, "Array")                             \
    T(String, "String")                           \
    T(Object, "Object")                           \


class Argument
{
public:
    Argument();
};


typedef std::list<Argument> Arguments;

}

#endif // ARGUMENT_H
