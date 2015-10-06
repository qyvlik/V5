#include <iostream>

#include "src/object.h"
#include "src/argument.h"

using namespace V5;
using namespace std;

int main()
{
    Object o;

    o.setObjectName("Nyou");

    Object::call fuck = findMethod<Object>("action");

    fuck(&o, Arguments());

    cout << o.toString() << endl;

    return 0;
}




