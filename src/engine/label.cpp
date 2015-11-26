#include "label.h"
#include <vector>

using namespace std;

Label::Label(const string &labelType, const string &labelNumber):
    labelType(labelType),
    labelNumber(labelNumber)
{

}

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

string Label::prefixion() const
{
    string label(this->labelNumber);
    return label.erase(label.find("#", 0), label.size());
}
/*
   enum LabelType {
        LABEL,
        LOOP_START_LABEL,
        LOOP_BODY_LABEL,
        LOOP_END_LABEL
    };
*/
bool Label::isLabel(const string &label)
{
    const static vector<string> LabelsType = {
        "LABEL",
        "LOOP_START_LABEL",
        "LOOP_BODY_LABEL",
        "LOOP_END_LABEL"
    };

    for(auto iter : LabelsType) {
        if(iter == label) {
            return true;
        }
    }
    return false;
}


