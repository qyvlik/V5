#include "instruction.h"


Instruction::Instruction(const std::string &operationType,
                         const std::string &arg0,
                         const std::string &arg1,
                         const std::string &arg2):
    operationType(operationType),
    arg0(arg0),
    arg1(arg1),
    arg2(arg2)
{

}
