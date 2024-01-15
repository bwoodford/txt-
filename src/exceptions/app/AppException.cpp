#include "AppException.h"

AppException::AppException(const std::string& msg) : std::runtime_error(msg) {}
