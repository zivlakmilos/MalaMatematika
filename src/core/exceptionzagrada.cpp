#include "core/exceptionzagrada.h"

ExceptionZagrada::ExceptionZagrada(int index)
    : Exception("Zagrada nije zatvorena"),
      m_index(index)
{
}

ExceptionZagrada::~ExceptionZagrada(void)
{
}
