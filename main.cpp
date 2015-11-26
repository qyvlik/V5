#include <iostream>
#include "src/parser/scanner.h"
#include "src/parser/parser.h"
#include "src/engine/instruction.h"
#include "src/engine/label.h"

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
    }

    bool getToken(string &tokenType, string &token) override {
        if(pos < tokenVector.size()) {
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

class ParserOutputStream : public Parser::OutputStream
{
public:
    virtual void output(const std::string& operationType,
                        const std::string& arg0,
                        const std::string& arg1,
                        const std::string& result) {
        instructionSet
                .push_back(
                    Instruction(operationType,
                                arg0,
                                arg1,
                                result));
    }

    std::vector<Instruction> getInstructionSet() const {
        return instructionSet;
    }

    //@Test
    void printInstructionSet()const {
        for (auto iter : instructionSet) {

            if(Label::isLabel(iter.operationType)) {
                cout  << iter.operationType << " "
                      << iter.arg0 << " :"
                      << endl;
            } else {
                cout << "\t"
                     << iter.operationType << ","
                     << iter.arg0 << ","
                     << iter.arg1 << ","
                     << iter.arg2 << endl;
            }
        }
    }

private:
    std::vector<Instruction> instructionSet;
};


int main(int ,
         char**
         argv
         )
{

    cout << argv[0] << endl;
    Scanner scanner("./test01.v5");
    if(scanner.scan()!=1) {
        scanner.printTokenList();

        Parser parser;

        Parser::InputStream* input =
                new TokenListInputStream(scanner.getTokenList());
        // Parser::OutputStream* output = Parser::getOutputStream("./test01.v5c");
        Parser::OutputStream* output = new ParserOutputStream();
        parser.parse(input, output);

        dynamic_cast<ParserOutputStream*>(output)->printInstructionSet();


        delete input;
        delete output;
    } else {
        cout << "open scan file fail!" << endl;
    }

    getchar();

    return 0;
}






