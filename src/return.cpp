#include "return.h"
#include "variant.h"

namespace V5 {


class ReturnPrivate
{
    ReturnPrivate() {

    }
    ~ReturnPrivate() {

    }
};

Return::Return():
    m_states(Normal)
{

}

Return::Return(Return::States states):
    m_states(states)
{
}

} //namespace V5

