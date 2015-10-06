#include "object.h"

#include <sstream>

using namespace std;

namespace V5 {


const pair<const string, Object::call> Object::ObjectMethodCallList[] = {
    {
        pair<const string, call>(
        "objectName",
        [&](Object* thiz, Arguments ) mutable -> Return {
            cout << thiz->objectName() << endl;
            return Return();
        })
    },
    {
        pair<const string, call>(
        "toString",
        [&](Object* thiz, Arguments ) mutable -> Return {
            thiz->toString();
            return Return();
        })
    }
};

const int Object::ObjectMethodCallCount =
        sizeof(Object::ObjectMethodCallList)
        /
        sizeof(Object::ObjectMethodCallList[0]);


Object::Object()
{

}

Object::~Object()
{

}


std::string Object::objectName() const
{
    return m_objectName;
}

void Object::setObjectName(const string &name)
{
    if(m_objectName != name) {
        m_objectName = name;
    }
}

string Object::toString() const
{
    stringstream ss;
    ss << this;
    string address;
    ss >> address;

    string s("Object(");
    s += address;
    s += m_objectName.empty() ? ")" : " ," + m_objectName + ")";
    return s;
}


} //namespace V5

