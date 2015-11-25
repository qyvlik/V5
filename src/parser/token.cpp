#include "token.h"

using namespace std;

const string Token::STRING = "STRING";

const string Token::CODESTRING = "CODESTRING";

const string Token::ID = "ID";

const string Token::NUMBER = "NUMBER";

const string Token::KEYWORD = "KEYWORD";

const string Token::ERROR = "ERROR";

const vector<string> Token::KeyWord = {
    "if", "else","true","false",
    "for", "while", "do",
    "switch", "case", "default",
    "return","break", "continue",
    "var", "int", "double", "float", "long",
    "class", "public", "protected", "private", "this",
    "try", "catch", "throw",
    "new", "delete", "null", "function"
};


const vector<string> Token::SingleWord = {
    "+", "-",
    "*", "%",                     // "/"

    "(", ")",
    "[", "]",
    "{", "}",

    ";", ",",

    "."                          //! 点域运算符
};


const vector<string> Token::DoubleWord = {
    ">", "<",
    "=", "!"
};


Token::Token()
{

}

Token::Token(const string &type, const string &value):
    tokenType(type),
    tokenValue(value)
{

}

Token::Token(const Token &token):
    tokenType(token.tokenType),
    tokenValue(token.tokenValue)
{

}

Token::~Token()
{

}

bool Token::isKeyWord(const string &word)
{
    for(size_t i=0; i<Token::KeyWord.size(); i++) {
        if(Token::KeyWord[i] == word) {
            return true;
        }
    }
    return false;
}

bool Token::isSingleWord(int word)
{
    for(size_t i=0; i<Token::SingleWord.size(); i++) {
        if(Token::SingleWord[i][0] == word) {
            return true;
        }
    }
    return false;
}

bool Token::isDoubleWord(int word)
{
    for(size_t i=0; i<Token::DoubleWord.size(); i++) {
        if(Token::DoubleWord[i][0] == word) {
            return true;
        }
    }
    return false;
}

string Token::getTokenType() const
{
    return tokenType;
}

void Token::setTokenType(const string &value)
{
    tokenType = value;
}

string Token::getTokenValue() const
{
    return tokenValue;
}

void Token::setTokenValue(const string &value)
{
    tokenValue = value;
}

void Token::clear()
{
    tokenType.clear();
    tokenValue.clear();
}

