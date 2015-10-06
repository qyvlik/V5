#ifndef RETURN_H
#define RETURN_H

#include "v5.h"

namespace V5 {

class ReturnPrivate;
class Return
{
public:
    enum States {
        Normal,
        NullCall,
        BarArguments
    };

    Return();
    Return(States states);

private:
    const States m_states;
    ReturnPrivate* d_ptr;

};


}

#endif // RETURN_H
