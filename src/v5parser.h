#ifndef V5PARSER_H
#define V5PARSER_H

#include "v5.h"

namespace V5 {


class LexicalParser;

class V5Parser
{
    enum Error {
        None = 0,
        HasError = 1,
        OpenFileFail = 2,
        Z
    };

public:

    explicit V5Parser();
//    ~V5Parser();

//    int lexicalParser(const std::string& filename);

//    TokenList& tokens();
//    const TokenList& tokens()const;

//private:
//    LexicalParser* m_lexicalParser;

};


} // namespace V5

#endif // V5PARSER_H
