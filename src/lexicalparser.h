#ifndef LEXICALPARSER_H
#define LEXICALPARSER_H

#include "v5.h"
#include <string>

namespace V5 {


class LexicalParser
{
public:
    enum Error {
        None = 0,
        HasError = 1,
        OpenFileFail = 2
    };

    LexicalParser();

    Error parser(const std::string& fileName);

    TokenList& tokens();
    const TokenList& tokens() const;

protected:
    static const char* KeywordList[];
    static const int KeywordCount;
    static const char* Singlewords;
    static const char* Doublewords;

private:
    TokenList m_tokens;
};


} // namespace V5

#endif // LEXICALPARSER_H
