#include "core/random.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

const int Random::FLOAT_GENERATOR_PRECISION;
const int Random::DOUBLE_GENERATOR_PRECISION;

bool Random::s_initialized = false;

Random::Random(void)
{
    if(s_initialized)
        return;

    s_initialized = true;
    srand(time(NULL));
}

Random::~Random(void)
{
}

int Random::nextInt(int n) const
{
    if(n < 0)
        n *= -1;

    return rand() % n;
}

float Random::nextFloat(void) const
{
    return nextInt(FLOAT_GENERATOR_PRECISION) / (float)FLOAT_GENERATOR_PRECISION;
}

double Random::nextDouble(void) const
{
    return nextInt(DOUBLE_GENERATOR_PRECISION) / (double)DOUBLE_GENERATOR_PRECISION;
}
