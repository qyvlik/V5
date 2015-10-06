#ifndef OBJECT_H
#define OBJECT_H

#include "v5.h"
#include "argument.h"
#include "return.h"
#include "variant.h"

#include <functional>
#include <map>

namespace V5 {

#define V5_INVOKABLE

#define V5_SCRIPT_OBJECT(_CLASS_NAME_) \
    public: \
    typedef std::function<Return(_CLASS_NAME_*, Arguments)> call; \
    static const std::pair<const std::string, call> ObjectMethodCallList[]; \
    static const int ObjectMethodCallCount; \
    private:

template <typename T>
static std::function<Return(T*, Arguments)> findMethod(const std::string& methodName)
{
    for(int iter=0; iter<T::ObjectMethodCallCount; iter++) {
        if(T::ObjectMethodCallList[iter].first == methodName) {
            return T::ObjectMethodCallList[iter].second;
        }
    }
    return [&](T*, Arguments) -> Return { return Return(); } ;
}

class Object
{
    V5_SCRIPT_OBJECT(Object);

public:
    Object();
    virtual ~Object();

    V5_INVOKABLE std::string objectName()const;
    V5_INVOKABLE void setObjectName(const std::string& name);

    V5_INVOKABLE virtual std::string toString() const;

private:
    std::string m_objectName;
};


} //namespace V5

#endif // OBJECT_H
