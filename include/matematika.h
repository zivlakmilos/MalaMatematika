#ifndef _MATEMATIKA_H_
#define _MATEMATIKA_H_

#include <vector>
#include <stdint.h>

enum Operator {
    OperatorPlus = 0,
    OperatorMinus,
    OperatorPuta,
    OperatorPodeljeno,
    OperatorZagradaOtvorena,
    OperatorZagradaZatvorena
};

enum TipElementaOperacije
{
    TipElementaOperacijeOperator = 0,
    TipElementaOperacijeOperand
};

struct ElementOperacije
{
    TipElementaOperacije tip;

    union
    {
        Operator operacija;
        uint32_t operand;
    } vrednost;
};

class Matematika
{
public:
    Matematika(void);
    ~Matematika(void);

    uint32_t racunajInfiksu(const std::vector<ElementOperacije> &formula);

    std::vector<ElementOperacije> pretvoriInfiksnuUPostfiksnu(const std::vector<ElementOperacije> &formula);

private:
    uint32_t izvrsiOperaciju(uint32_t operand1, uint32_t operand2, Operator operacija);
};

#endif // _MATEMATIKA_H_
