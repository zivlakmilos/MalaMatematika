#include "core/exception.h"

Exception::Exception(std::string what, int code)
    : m_what(what),
      m_code(code)
{
}

Exception::~Exception(void)
{
}

const char *Exception::what(void) const throw()
{
    return m_what.c_str();
}

int Exception::errorCode(void)
{
    return m_code;
}
