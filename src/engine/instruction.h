#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

// 指令

class Instruction
{
public:
    Instruction(const std::string& operationType,
                const std::string& arg0,
                const std::string& arg1,
                const std::string& arg2);


    std::string operationType;
    std::string arg0;
    std::string arg1;
    std::string arg2;
};

#endif // INSTRUCTION_H
