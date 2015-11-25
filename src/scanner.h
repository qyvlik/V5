#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>

#include "v5.h"

namespace V5 {

V5_INTERFACE CharacterStream
{
public:

    enum Error {
        OpenFail,
        Unknown
    };

    explicit CharacterStream();
    virtual ~CharacterStream();

    virtual int64_t size() = 0;
    virtual int64_t position() = 0;
    virtual int64_t line() = 0;
    virtual int64_t linePosition() = 0;

    // get a char, return true on success
    virtual bool getChar(int* c);

    virtual book isSeekable() = 0;
    virtual void seek(int64_t pos) = 0;

    virtual bool isOpen() = 0;
    virtual void open() = 0;
    virtual void close() = 0;

    virtual bool atEnd() = 0;
    virtual Error error() = 0;
};



class Scanner
{

public:

    enum Error {

    };



    explicit Scanner(CharacterStream* stream);
    virtual ~Scanner();

private:
    CharacterStream* m_characterStream;
};


}

#endif // SCANNER_H
