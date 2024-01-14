#include "TerminalException.h"

TerminalException::TerminalException(const std::string& msg) : std::runtime_error(msg) {}
