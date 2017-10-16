#ifndef _RANDOM_H_
#define _RANDOM_H_

class Random
{
public:
    Random(void);
    ~Random(void);

    int nextInt(int n) const;
    float nextFloat(void) const;
    double nextDouble(void) const;
    double nextGaussian(void);

private:
    static const int FLOAT_GENERATOR_PRECISION      = 1000;
    static const int DOUBLE_GENERATOR_PRECISION     = 1000;

    static bool s_initialized;
};

#endif // _RANDOM_H_
