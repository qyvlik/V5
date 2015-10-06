#include <iostream>

#include "src/object.h"
#include "src/arguments.h"

using namespace V5;
using namespace std;

int main()
{
    Object o;
    o.objectName();

    Object::call fuck = findMethod<Object>("fuck");

    fuck(&o, Arguments());

    return 0;
}




