#pragma once

#include <iostream>
#include <exception>

class LexException: public std::exception {
private:
    const char* errMsg;

public:
    explicit LexException(const char* msg) : errMsg(msg)
    {
    }

    virtual const char* what() const throw() {
        return errMsg;
    }
};