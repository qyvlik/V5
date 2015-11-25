#include <iostream>
#include "src/parser/scanner.h"

using namespace std;

int main(int , char** )
{
    Scanner scanner("./test01.v5");
    scanner.scan();
    scanner.printTokenList();

    return 0;
}




