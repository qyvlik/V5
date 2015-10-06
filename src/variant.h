#ifndef VARIANT_H
#define VARIANT_H

#include "v5.h"

namespace V5 {

#define VARIANT_TYPE_LIST(T, K)                   \
    T(Invalid, "Invalid")                         \
    T(Bool, "Bool")                               \
    T(Int, "Int")                                 \
    T(Long, "Long")                               \
    T(Double, "Double")                           \
    T(Char, "Char")                               \
    T(Array, "Array")                             \
    T(String, "String")                           \
    T(Object, "Object")                           \

class VariantPrivate;

class Variant
{
public:

#define T(name, string) name,
    enum Type {
        VARIANT_TYPE_LIST(T,T)
        TypeNumbers,
        LastType = 0xfffffff
    };
#undef T

    Variant();
    bool isValid() const ;
private:
    VariantPrivate* d_ptr;

};


} //namespace V5

#endif // VARIANT_H
