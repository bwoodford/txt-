#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <stdexcept>
#include <string>

class AppException : public std::runtime_error {
public:
    AppException(const std::string& msg);
};

#endif
