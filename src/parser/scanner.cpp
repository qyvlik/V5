#include "scanner.h"

#include <unistd.h>

using namespace std;

Scanner::Scanner(const std::string &filename):
    inputStream(new InputStream(filename)),
    outputStream(new OutputStream),
    letter(0)
{

}

Scanner::~Scanner()
{
    delete inputStream;
}

bool Scanner::setScanFile(const string &filename)
{
    return inputStream->open(filename);
}

void Scanner::clear()
{
    inputStream->close();
    outputStream->clear();
}

int Scanner::scan()
{
    if(!inputStream->isOpen()) {

        cerr << "open file fail!" << endl;
        return 1;
    }

    letter = inputStream->get();

    while(letter != EOF) {
        if(isspace(letter)) {
            removeSpace();
        }

        if(isalpha(letter)) {
            alphaToken();
        } else if(isdigit(letter)) {
            digitToken();
        } else if(Token::isSingleWord(letter)) {
            singleWordToken();
        } else if(Token::isDoubleWord(letter)) {
            doubleWordToken();
        } else if(letter == '/') {
            commentToken();
        } else if(letter == '\"' || letter == '\'' || letter == '`') {
            stringToken();
        }
        /*
        else {
            outputStream->error( inputStream->streamName(),
                                 inputStream->lineNumber(),
                                 inputStream->columnNumber(),
                                 "Not allow token"
                                 );
            // token.clear();
            // token.push_back(letter);
            // letter = inputStream->get();
            // outputStream->error(Scanner::ERROR,token);
            return 1;
        }
        */
    }
    return 0;
}

std::list<Token> Scanner::getTokenList() const
{
    return outputStream->tokenList;
}

void Scanner::removeSpace()
{
    while(isspace(letter)) {
        letter = inputStream->get();
    }
}

void Scanner::alphaToken()
{
    token.clear();
    while(isalnum(letter)) {
        token.push_back(letter);
        letter = inputStream->get();
    }
    //! 查保留字
    if(Token::isKeyWord(token)) {
        outputStream->output(Token(Token::KEYWORD, token));
    } else {
        outputStream->output(Token(Token::ID, token));
    }
}

void Scanner::digitToken()
{
    token.clear();

    // int dot = 0;                        // 检查遇到 '.' 的个数
    while(isdigit(letter)) {
        token.push_back(letter);
        letter = inputStream->get();
    }
    outputStream->output(Token(Token::NUMBER, token));
}

void Scanner::singleWordToken()
{
    token.clear();
    token.push_back(letter);
    outputStream->output(Token(token, token));
    letter = inputStream->get();
}

void Scanner::doubleWordToken()
{
    token.clear();
    token.push_back(letter);
    letter = inputStream->get();

    if(letter == '=') {
        token.push_back(letter);
        letter = inputStream->get();
    }
    outputStream->output(Token(token, token));
}

void Scanner::commentToken()
{
    token.clear();
    letter = inputStream->get();
    if(letter == '*') {
        int letter1 = inputStream->get();
        do {
            letter = letter1;
            letter1 = inputStream->get();
        } while((letter != '*' || letter != '/') && letter1 != EOF);
    } else {
        token.push_back('/');
        outputStream->output(Token(token, token));
        letter = inputStream->get();
    }
}

void Scanner::stringToken()
{
    int flag = 0;
    bool error = false;
    if(letter == '"') {
        flag = '"';
    } else if(letter == '\'') {
        flag = '\'';


        //! `var codestring = "string"; `
        //!  code string ,can inject into the c++ runtime
    } else {
        flag = '`';
    }

    token.clear();

    letter = inputStream->get();
    while(letter != flag && letter != EOF) {
        //! 字符串中不允许直接出现回车，回车必须以 \n 转义
        //! 如果是直接丢给虚拟机执行，就不用转义了。
        //        if(letter == '\n') {
        //            error = true;
        //            break;
        //        }

        //! 转义处理
        //! 直接转义到内存中
        //! 其实不建议直接转义
        //! 因为要输出字符串字面量
        //! 当然如果不输出到文件，就可以直接转义
        //! 这里建议不要生成中间文件
        //! 直接转义到内存中
        //! 然后在内存中直接通过语法解析然后直接丢给虚拟机执行。
        //! 所以转义直接在虚拟机中进行
        if(letter == '\\' ) {

            letter = inputStream->get();
            switch (letter)
            {
            case 'a':
                token.push_back('\a'); letter = inputStream->get(); continue;
            case 'b':
                token.push_back('\b'); letter = inputStream->get(); continue;
            case 'f':
                token.push_back('\f'); letter = inputStream->get(); continue;
            case 'n':
                token.push_back('\n'); letter = inputStream->get(); continue;
            case 'r':
                token.push_back('\r'); letter = inputStream->get(); continue;
            case 't':
                token.push_back('\t'); letter = inputStream->get(); continue;
            case 'v':
                token.push_back('\v'); letter = inputStream->get(); continue;
            case '\\':
                token.push_back('\\'); letter = inputStream->get(); continue;
            case '\'':
                token.push_back('\''); letter = inputStream->get(); continue;
            case '"':
                token.push_back('\"'); letter = inputStream->get(); continue;
            case '`':
                token.push_back('`'); letter = inputStream->get(); continue;
            default:
                break;
            }
        }
        token.push_back(letter);
        letter = inputStream->get();
    }

    if(letter != EOF && !error) {
        outputStream->output(Token(Token::STRING, token));
    } else {
        outputStream->error( inputStream->streamName(),
                             inputStream->lineNumber(),
                             inputStream->columnNumber(),
                             "End of file"
                             );
        return ;
    }
    letter = inputStream->get();
}

//-------------------------------------------------------------------------

Scanner::InputStream::InputStream(const std::string &filename):
    m_filename(filename),
    m_lineNumber(1),
    m_columnNumber(0),
    fread( filename
           , std::ios_base::binary | std::ios_base::in
           )
{
}

Scanner::InputStream::~InputStream(){
    fread.close();
}

bool Scanner::InputStream::open(const string &filename)
{
    fread.clear();
    fread.close();
    fread.open(filename, std::ios_base::binary | std::ios_base::in);
    m_lineNumber = 1;
    m_columnNumber = 0;
    m_filename = filename;
    return fread.is_open();
}

bool Scanner::InputStream::isOpen() const {
    return fread.is_open();
}

int Scanner::InputStream::get(){
    int g = fread.get();
    ++m_columnNumber;
    if(g == '\n') {
        m_columnNumber = 0;
        ++m_lineNumber;
    }
    return g;
}

int Scanner::InputStream::lineNumber() const{
    return m_lineNumber;
}

int Scanner::InputStream::columnNumber() const {
    return m_columnNumber;
}

std::string Scanner::InputStream::streamName() const{
    return m_filename;
}

void Scanner::InputStream::close(){
    m_lineNumber = 1;
    m_columnNumber = 0;
    m_filename.clear();
    fread.close();
}

//-----------------------------------------------------------------------------

void Scanner::OutputStream::clear()
{
    tokenList.clear();
}

void Scanner::OutputStream::output(const Token &token)
{
    tokenList.push_back(token);
}

void Scanner::OutputStream::error(const std::string &filename,
                                  int lineNumber,
                                  int columnNumber,
                                  const std::string &reason)
{
    cout << "filename: "<< filename
         << " [" << lineNumber << ":" << columnNumber << "] : \n"
         <<  reason << endl;
}
