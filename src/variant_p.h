#ifndef VARIANTPRIVATE_H
#define VARIANTPRIVATE_H


#include "variant.h"

namespace V5 {

//T(Invalid, "Invalid")
//T(Bool, "Bool")
//T(Int, "Int")
//T(Long, "Long")
//T(Double, "Double")
//T(Char, "Char")
//T(Array, "Array")
//T(String, "String")
//T(Object, "Object")

class VariantPrivate
{
public:

#define T(name, string) name,
    enum Type {
        VARIANT_TYPE_LIST(T,T)
        TypeNumbers,
        LastType = 0xfffffff
    };
#undef T

    VariantPrivate();
    ~VariantPrivate();

    union u {
        bool* bool_;
        int * int_;
        long long int * long_;
        double* double_;
        std::string* string_;
        V5::Object* object_;
    };

private:
    Type m_type;
    u* m_data;
};


} // namespace V5

#endif // VARIANTPRIVATE_H
