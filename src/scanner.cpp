#include "scanner.h"

namespace V5 {


Scanner::Scanner(CharacterStream *stream):
    m_characterStream(stream)
{

}

Scanner::~Scanner()
{
    m_characterStream->close();
}


}
