#pragma once

#include <iostream>
#include <exception>

class ParseException: public std::exception {
private:
    const char* errMsg;

public:
    explicit ParseException(const char* msg) : errMsg(msg)
    {
    }

    virtual const char* what() const throw() {
        return errMsg;
    }
};