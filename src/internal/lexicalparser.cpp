#include "lexicalparser.h"

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

namespace V5 {


const char* LexicalParser::KeywordList[] = {
    "if",
    "else",
    "for",
    "while",
    "do",
    "int",
    "read",
    "write"
};

const int LexicalParser::KeywordCount =
        sizeof(LexicalParser::KeywordList)
        /
        sizeof(LexicalParser::KeywordList[0]);

const char* LexicalParser::Singlewords = "+-*(){};,:";

const char* LexicalParser::Doublewords = "><=!";



LexicalParser::LexicalParser()
{

}

LexicalParser::Error LexicalParser::parser(const string &fileName)
{
    ifstream sourceFile(fileName);
    if(!sourceFile.is_open()){
        return Error::OpenFileFail;
    }

    string token;
    int n = 0;
    char word;

    word = sourceFile.get();
    while(word != EOF) {
        while(word == ' ' || word == '\n' || word == '\t')
            word = sourceFile.get();

        if(isalpha(word)) {
            token.clear();
            token.push_back(word);
            word = sourceFile.get();
            while(isalnum(word)) {
                token.push_back(word);
                word =sourceFile.get();
            }

            //! [检查是否为保留字]
            n = 0;
            while( n<KeywordCount && strcmp(token.data(), KeywordList[n]))
                n++;

            if(n >= KeywordCount) {
                m_tokens.push_back(Token(Token::IDENTIFIER, token));
            } else {
                m_tokens.push_back(Token(Token::findType(token), token));
            }
            //! [检查是否为保留字]

        } else if(isdigit(word)) {
            token.clear();
            token.push_back(word);
            word = sourceFile.get();
            while(isdigit(word)) {
                token.push_back(word);
                word = sourceFile.get();
            }
            m_tokens.push_back(Token(Token::NUMBER, token));

        } else if (strchr(Singlewords, word)!=NULL) {
            token.clear();
            token.push_back(word);
            word = sourceFile.get();
            m_tokens.push_back(Token(Token::IDENTIFIER, token));

        } else if (strchr(Doublewords, word)!=NULL) {
            token.clear();
            token.push_back(word);
            word = sourceFile.get();
            if(word == '=') {
                token.push_back(word);
                word = sourceFile.get();
            } else {
                token.push_back('\0');
            }
            m_tokens.push_back(Token(Token::IDENTIFIER, token));

            //! 过滤注释
        } else if(word == '/') {
            word = sourceFile.get();
            if(word == '*') {
                char ch1 = sourceFile.get();
                do {
                    word = ch1;
                    ch1 = sourceFile.get();
                } while((word != '*' || word != '/') && ch1 != EOF );
                word = sourceFile.get();
            } else {
                token.clear();
                token.append("/\0");
                m_tokens.push_back(Token(Token::IDENTIFIER, token));
            }
        }

        //! 过滤字符串
        else if(word == '"') {
            token.clear();
            word = sourceFile.get();
            while(word != '"') {
                token.push_back(word);
                word = sourceFile.get();

                if(word == '"') {
                    word = sourceFile.get();
                    break;
                } else if(word == '\\') {

                    //! 此处为转义处理
                    do {
                        word = sourceFile.get();
                        if(word == EOF) {
                            m_tokens.push_back(Token(Token::ERROR, token));
                            return Error::HasError;;
                        }
                        token.push_back(word);
                        word = sourceFile.get();
                    } while(word == '\\');
                    //! 此处为转义处理
                }
            }
            word = sourceFile.get();
            m_tokens.push_back(Token(Token::STRING, token));
        }

        else {
            token.clear();
            token.push_back(word);
            word = sourceFile.get();
            m_tokens.push_back(Token(Token::ERROR, token));
            sourceFile.close();
            return Error::HasError;
        }
    }

    sourceFile.close();
    return Error::None;
}

TokenList &LexicalParser::tokens()
{
    return m_tokens;
}

const TokenList &LexicalParser::tokens() const
{
    return m_tokens;
}


} // namespace V5
