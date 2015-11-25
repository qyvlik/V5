#include <iostream>
#include "src/parser/scanner.h"
#include "src/parser/parser.h"

using namespace std;
//! [STL-容器间的复制list&vector](http://cooker.iteye.com/blog/689202)
class TokenListInputStream : public Parser::InputStream
{
public:
    TokenListInputStream(const std::list<Token> & tokenList):
        pos(0)
    {
        std::copy(tokenList.begin(),
                  tokenList.end(),
                  std::back_inserter(tokenVector));
        tokenVector.push_back(Token());  // push a null token
    }

    bool getToken(string &tokenType, string &token) override {
        if(pos <= tokenVector.size()) {
            tokenType = tokenVector.at(pos).getTokenType();
            token = tokenVector.at(pos).getTokenValue();
            pos+=1;
            return true;
        }
        return false;
    }

    size_t tell() override {
        return pos;
    }

    void seek(size_t pos) override {
        this->pos = pos;
    }

    bool isEnd() override {
        return this->pos >= (tokenVector.size()-1);
    }


private:
    std::vector<Token> tokenVector;
    size_t pos;
};


int main(int , char** )
{
    Scanner scanner("./test01.v5");
    scanner.scan();
    scanner.printTokenList();

    Parser parser;

    Parser::InputStream* input = new TokenListInputStream(scanner.getTokenList());
    Parser::OutputStream* output = Parser::getOutputStream("./test01.v5c");
    parser.parse(input, output);


    return 0;
}




