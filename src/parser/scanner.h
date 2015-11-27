#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <iostream>
#include <fstream>
#include <list>

class Scanner
{
public:
    explicit Scanner(const std::string& filename);
    ~Scanner();

    bool setScanFile(const std::string& filename);

    void clear();

    int scan();

    std::list<Token> getTokenList() const;

    //@Test
    void printTokenList() const {
        auto tokens = this->getTokenList();
        auto iter = tokens.begin();
        auto end = tokens.end();
        while(iter != end) {

            std::cout << "(" << (*iter).getTokenType()
                      << ","
                      << (*iter).getTokenValue() << ")"
                      << std::endl;

            iter++;
        }
    }

private:
    // 去除空格，制表符，回车
    void removeSpace();

    // alpha
    void alphaToken();

    void digitToken();

    void singleWordToken();

    void doubleWordToken();

    void commentToken();

    void stringToken();

protected:
    class InputStream
    {
    public:
        explicit InputStream(const std::string& filename);
        ~InputStream();
        bool open(const std::string &filename);
        bool isOpen()const;
        int get();
        int lineNumber() const;
        int columnNumber() const;
        std::string streamName() const;
        void close();
    private:
        std::string m_filename;
        int m_lineNumber;
        int m_columnNumber;
        std::ifstream fread;
        friend class Scanner;
    };

    class OutputStream {
    public:
        explicit OutputStream()
        { }

        virtual ~OutputStream()
        { }

        virtual void clear();
        virtual void output(const Token& token);
        virtual void error(const std::string& filename,
                           int lineNumber,
                           int columnNumber,
                           const std::string& reason);
    private:
        std::list<Token> tokenList;
        friend class Scanner;
    };

private:
    InputStream* inputStream;
    OutputStream* outputStream;
    int letter;
    std::string token;
};

#endif // SCANNER_H
