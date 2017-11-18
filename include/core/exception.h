#ifndef _Z_EXCEPTION_H_
#define _Z_EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception(std::string what = "", int code = 0);
    virtual ~Exception(void);

    virtual const char *what(void) const throw() override;
    virtual int errorCode(void);

private:
    std::string m_what;
    int m_code;
};

#endif // _Z_EXCEPTION_H_
