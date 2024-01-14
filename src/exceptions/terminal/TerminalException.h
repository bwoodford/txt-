#ifndef TERMINALEXCEPTION_H
#define TERMINALEXCEPTION_H

#include <stdexcept>
#include <string>

class TerminalException : public std::runtime_error {
public:
    TerminalException(const std::string& msg);
};

#endif
