#ifndef _EXCEPTION_ZAGRADA_H_
#define _EXCEPTION_ZAGRADA_H_

#include "core/exception.h"

class ExceptionZagrada : public Exception
{
public:
    ExceptionZagrada(int index);
    virtual ~ExceptionZagrada(void);

    inline int index(void) { return m_index; }

private:
    int m_index;
};

#endif // _EXCEPTION_ZAGRADA_H_
