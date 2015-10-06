#include "object.h"

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
        "fuck",
        [&](Object* thiz, Arguments ) mutable -> Return {
            thiz->fuck();
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

std::string Object::objectName() const
{
    return m_objectName;
}

void Object::fuck()
{
    cout << "call fuck..." << endl;
}


}

