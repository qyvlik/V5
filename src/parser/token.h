#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

class Token
{
public:
    Token();
    Token(const std::string& type, const std::string& value);
    Token(const Token& token);
    ~Token();

    static const std::string STRING;
    static const std::string CODESTRING;
    static const std::string ID;
    static const std::string NUMBER;
    static const std::string KEYWORD;
    static const std::string ERROR;

    static const std::string LABEL;
    static const std::string LOOP_START_LABEL;
    static const std::string LOOP_BODY_LABEL;
    static const std::string LOOP_END_LABEL;

    static const std::string LOOP_GOTO;
    static const std::string LOOP_JUMP;

    static const std::string GOTO;

    std::string getTokenType() const;

    void setTokenType(const std::string &value);

    std::string getTokenValue() const;

    void setTokenValue(const std::string &value);

    void clear();

    static bool isKeyWord(const std::string& word);

    static bool isSingleWord(int word);

    static bool isDoubleWord(int word);

    static bool isDeclaraWord(const std::string &word);

    static const std::vector<std::string> KeyWord;

    static const std::vector<std::string> SingleWord;

    static const std::vector<std::string> DoubleWord;

private:
    std::string tokenType;
    std::string tokenValue;
};

#endif // TOKEN_H
