#ifndef LABEL_H
#define LABEL_H

#include <string>


// 标签有两种
// 一种是if-else 的跳转标签
// 另一种是循环的调整标签
// 循环的跳转标签有
// LOOP_START_LABEL
// LOOP_BODY_LABEL
// LOOP_END_LABEL
// (LOOP_GOTO, $0, 0#1, 0#2)
// 0#1 意思是0为前缀，长度加1
// 0#2 疑似是0为前缀，长度加2
// LOOP_GOTO 的arg1,arg2
// arg1 是 LOOP_BODY_LABEL
// arg2 是 LOOP_END_LABEL

class Label
{
public:
    Label(const std::string& labelType, const std::string& labelNumber);
    std::string prefixion() const;

    static bool isLabel(const std::string& label);

private:
    std::string labelType;
    std::string labelNumber;
};

#endif // LABEL_H
